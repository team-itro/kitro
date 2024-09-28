import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

# Constants from the original function
SHARP_CONST_A = 35.93  # Example values, adjust based on your specific sensor
SHARP_CONST_B = -2.1995
SHARP_CONST_C = 1.7021


def find_params():
    # Voltage values from the graph
    VOLTAGE_DATA = np.array(
        [
            1.9,
            1.55,
            1.30,
            1.10,
            0.97,
            0.86,
            0.79,
            0.72,
            0.65,
            0.61,
            0.58,
            0.53,
            0.49,
            0.45,
        ]
    )

    ADC8BIT_DATA = np.array([0, 2, 5, 10, 15, 20])  # Distances in cm

    # Corresponding distance values from the graph
    DISTANCE_DATA = np.array(
        [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
    )  # Distances in cm

    # Fit the curve and get a, b, c
    SHARP_CONST_A, SHARP_CONST_B, SHARP_CONST_C = fit_curve(VOLTAGE_DATA, DISTANCE_DATA)
    print(
        f"fitted parameters: a = {SHARP_CONST_A}, b = {SHARP_CONST_B}, c = {SHARP_CONST_C}"
    )

    # Plot the original data and fitted curve
    plot_fitted_curve(
        VOLTAGE_DATA, DISTANCE_DATA, SHARP_CONST_A, SHARP_CONST_B, SHARP_CONST_C
    )


def lut_gen_wrapper():
    # Generate and print the lookup table
    lookup_table = generate_lookup_table()

    # Optionally print the table for use in C code
    for idx, value in enumerate(lookup_table):
        print(f"{value:.2f}f,", end="")
        if (idx + 1) % 8 == 0:  # Format it nicely, 8 values per line
            print()


def generate_lookup_table():
    # Generate lookup table for ADC values from 0 to 255
    lookup_table = []

    for adc_value in range(256):
        # Convert ADC value to voltage (assuming 8-bit ADC, max 3.3V)
        voltage = adc_value * (3.3 / 255.0)

        # Apply the exponential distance formula
        distance = SHARP_CONST_A * np.exp(SHARP_CONST_B * voltage) + SHARP_CONST_C

        # Clamp distance between 2.0 and 15.0
        if distance < 2.0:
            distance = 2.0
        elif distance > 15.0:
            distance = 15.0

        # Append the distance to the lookup table
        lookup_table.append(distance)

    return lookup_table


# Define the exponential model function
def exponential_model(voltage, a, b, c):
    return a * np.exp(-b * voltage) + c


# Function to perform curve fitting
def fit_curve(voltage_data, distance_data):
    # Use curve_fit to find the optimal values for a, b, c
    popt, _ = curve_fit(exponential_model, voltage_data, distance_data)

    # popt contains the optimal values for a, b, c
    a, b, c = popt
    return a, b, c


# Function to plot the original data and the fitted curve
def plot_fitted_curve(voltage_data, distance_data, a, b, c):
    # Generate voltage values for the curve (finer resolution)
    voltage_fit = np.linspace(min(voltage_data), max(voltage_data), 100)

    # Calculate the corresponding fitted distance values
    distance_fit = exponential_model(voltage_fit, a, b, c)

    # Plot the original data points
    plt.scatter(voltage_data, distance_data, color="red", label="Original Data")

    # Plot the fitted curve
    plt.plot(voltage_fit, distance_fit, color="blue", label="Fitted Curve")

    # Label the axes
    plt.xlabel("Analog Voltage Output [V]")
    plt.ylabel("Distance to Reflective Object [cm]")

    # Add a legend
    plt.legend()

    # Display the plot
    plt.show()


# Example usage
if __name__ == "__main__":
    find_params()
    # lut_gen_wrapper()
