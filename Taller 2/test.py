def find_tank(capacities, water):
    """
    Finds the highest tank that can be filled with water to reach the first tank.

    Args:
        capacities: A list of tank capacities.
        water: The total amount of water.

    Returns:
        The index of the highest tank, or -1 if no tank can be filled.
    """

    remaining_water = water
    for i in range(len(capacities) - 1, 0, -1):
        if capacities[i] >= remaining_water:
            return i
        remaining_water -= capacities[i]
    return -1

# Read input
n, q = map(int, input().split())
capacities = list(map(int, input().split()))

# Process queries
for _ in range(q):
    k = int(input())
    result = find_tank(capacities, k)
    print(result)
