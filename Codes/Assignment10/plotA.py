import matplotlib.pyplot as plt

# Data from your experiments (adjust these based on your actual results)
num_processes = [1, 2, 3, 4, 5, 6]
time_taken = [0.079482, 0.051666,0.041979,0.037728,0.037469,0.043751]

# Create the plot
plt.plot(num_processes, time_taken, marker='o', color='b')

# Add labels and title
plt.xlabel('Number of Processes')
plt.ylabel('Time Taken (Seconds)')
plt.title('Performance of MPI Broadcast with Fixed Message Size')

# Show the plot
plt.grid(True)
plt.show()
