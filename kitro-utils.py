import numpy as np

# Constants from the original function
SHARP_CONST_A = 35.93  # Example values, adjust based on your specific sensor
SHARP_CONST_B = -2.1995
SHARP_CONST_C = 1.7021

# define SHARP_CONST_A 35.93f
# define SHARP_CONST_B -2.1995f
# define SHARP_CONST_C 1.7021f


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


# Generate and print the lookup table
lookup_table = generate_lookup_table()

# Optionally print the table for use in C code
for idx, value in enumerate(lookup_table):
    print(f"{value:.2f}f,", end="")
    if (idx + 1) % 8 == 0:  # Format it nicely, 8 values per line
        print()
