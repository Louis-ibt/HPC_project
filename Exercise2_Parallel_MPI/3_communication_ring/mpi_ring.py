"""
MPI Communication Ring  (Exercise 1 – last bullet)
====================================================
Run with:   mpirun -n <N> python mpi_ring.py

Among n processes:
  • process r  receives value 1000+(r-1) from rank r-1,  1 ≤ r ≤ n-1
  • process 0  receives value 1000+(n-1) from rank n-1
"""

from mpi4py import MPI

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
n    = comm.Get_size()

# Value that THIS process will SEND to the right neighbour
send_val = 1000 + rank

# Determine neighbours (ring topology)
right = (rank + 1) % n
left  = (rank - 1) % n

# Non-blocking send/receive to avoid deadlock
req = comm.isend(send_val, dest=right, tag=0)
recv_val = comm.recv(source=left, tag=0)
req.Wait()

expected = 1000 + left
print(f"Process {rank}/{n}: received {recv_val} from rank {left}  "
      f"(expected {expected})  ✓" if recv_val == expected else
      f"Process {rank}/{n}: ERROR – received {recv_val}, expected {expected}")
