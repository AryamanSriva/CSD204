import matplotlib.pyplot as plt

pthread_times = [0.085274, 0.089784, 0.084026, 0.075228, 0.089356]  
num_threads = [10, 20, 30, 40, 50]

plt.plot( num_threads,pthread_times, label='Average Time')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (miliseconds)')
plt.title('Performance of Bounded-CAS')
plt.legend()
plt.grid(True)
plt.show()


pthread_times = [0.89573, 1.3579, 2.9564, 1.8556, 2.7288]  
num_threads = [10, 20, 30, 40, 50]

plt.plot( num_threads,pthread_times, label='Average Time')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (miliseconds)')
plt.title('Performance of CAS')
plt.legend()
plt.grid(True)
plt.show()


pthread_times = [1.9562, 1.8956, 2.8436, 2.9463, 3.9464]  
num_threads = [10, 20, 30, 40, 50]

plt.plot( num_threads,pthread_times, label='Average Time')

plt.xlabel('Number of Threads')
plt.ylabel('Time Taken (miliseconds)')
plt.title('Performance of TAS')
plt.legend()
plt.grid(True)
plt.show()