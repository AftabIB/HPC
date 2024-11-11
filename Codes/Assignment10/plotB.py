import matplotlib.pyplot as plt

sizes = []
times = []

with open("timing_data.txt", "r") as f:
    for line in f:
        if "Average time" in line:
            print(f"Processing line: {line.strip()}")
            parts = line.split()
            try:
                size_str = parts[7].rstrip(":")
                size = int(size_str)
                time = float(parts[-2])
                sizes.append(size)
                times.append(time)
            except ValueError as e:
                print(f"Error converting parts: {parts} - {e}")

if not sizes or not times:
    print("No valid sizes or times found.")
else:
    plt.figure(figsize=(10, 6))
    plt.plot(sizes, times, marker="o")
    plt.xscale("log")
    plt.yscale("log")
    plt.title("MPI Reduce Average Time vs Message Size")
    plt.xlabel("Message Size (bytes)")
    plt.ylabel("Average Time (seconds)")
    plt.grid(True)
    plt.xticks(sizes)
    plt.show()
