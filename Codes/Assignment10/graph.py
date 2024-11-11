import matplotlib.pyplot as plt
import numpy as np

# Simulated data for testing (replace this with your actual data extraction)
sizes = [1, 10, 100, 1000, 10000]
times = [0.001, 0.01, 0.1, 1, 10]  # Replace with realistic average times

# Plotting the average time for reduce operation
plt.figure(figsize=(10, 6))
plt.plot(sizes, times, marker='o')
plt.xlabel('Process Size')
plt.ylabel('Average Time (secs)')
plt.title('Average Time for Reduce Operation')
plt.grid(True)
plt.xscale('log')
plt.yscale('log')
plt.savefig('GraphB.png')

# Simulated data for processes (replace this with your actual data extraction)
process_sizes = [1, 2, 3, 4, 5, 6]
process_times = [0.1, 0.05, 0.033, 0.025, 0.02, 0.018]  # Replace with realistic times

# Plotting the average time for process
plt.figure()
plt.plot(process_sizes, process_times, marker='o')
plt.xlabel('No of Processes')
plt.ylabel('Average Time (secs)')
plt.title('Average Time for Process')
plt.grid(True)
plt.xscale('log')
plt.yscale('log')
plt.savefig('GraphB-Process.png')
