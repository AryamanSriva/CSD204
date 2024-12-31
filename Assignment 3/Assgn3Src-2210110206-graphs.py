import matplotlib.pyplot as plt

# Experiment 1
sudoku_sizes = [4, 9, 16, 25]
single_thread_times = [716, 756, 1113, 687]  
omp_times = [931, 681, 746, 1119] 
pthread_times = [11876, 5141, 9431, 9319]  

plt.plot(sudoku_sizes, single_thread_times, label='Single Thread')
plt.plot(sudoku_sizes, omp_times, label='OpenMP')
plt.plot(sudoku_sizes, pthread_times, label='pthread')

plt.xlabel('Sudoku Size')
plt.ylabel('Time Taken (microseconds)')
plt.title('Performance Comparison with Varying Sudoku Size')
plt.legend()
plt.grid(True)
plt.show()

# Experiment 2
num_threads = [2, 4, 8, 16]
single_thread_time = 726  
omp_times = [941, 674, 594, 642] 
pthread_times = [796, 875, 732, 948] 

plt.plot(num_threads, [single_thread_time] * len(num_threads), label='Single Thread')
plt.plot(num_threads, omp_times, label='OpenMP')
plt.plot(num_threads, pthread_times, label='pthread')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (microseconds)')
plt.title('Performance Comparison with Varying Number of Threads')
plt.legend()
plt.grid(True)
plt.show()
