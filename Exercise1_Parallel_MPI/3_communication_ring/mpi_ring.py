"""
MPI Communication Ring  (Exercise 1 – last bullet)
====================================================
Run with:   mpirun -n <N> python mpi_ring.py
            (or: mpiexec -n <N> python mpi_ring.py  on Windows)

Among n processes:
  • process r  receives value 1000+(r-1) from rank r-1,  1 ≤ r ≤ n-1
  • process 0  receives value 1000+(n-1) from rank n-1

REQUIREMENTS:
  - mpi4py: pip install mpi4py
  - MPI library: Microsoft MPI (Windows) or OpenMPI/MPICH (Linux/Mac)
"""

import sys
from pathlib import Path

# Error handling for MPI
try:
    from mpi4py import MPI
except ImportError:
    print("ERROR: mpi4py not installed!")
    print("  Install with: pip install mpi4py")
    sys.exit(1)
except RuntimeError as e:
    print("ERROR: MPI library not found!")
    print("  Windows: Install Microsoft MPI from https://www.microsoft.com/en-us/download/details.aspx?id=57467")
    print("  Linux:   sudo apt-get install libopenmpi-dev openmpi-bin")
    print("  macOS:   brew install open-mpi")
    print(f"\nDetails: {e}")
    sys.exit(1)

# Setup output directory
OUTPUT_DIR = Path(__file__).parent.parent.parent.parent / "outputs" / "Exercise1_Parallel_MPI"
OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

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
status = "[OK]" if recv_val == expected else "[FAIL]"
message = (f"Process {rank}/{n}: received {recv_val} from rank {left}  "
           f"(expected {expected})  {status}")
print(message)

# Log results to file (only rank 0 to avoid race conditions)
if rank == 0:
    log_file = OUTPUT_DIR / f"ring_{n}procs.log"
    with open(log_file, "w") as f:
        f.write(f"MPI Ring Communication Test (n={n} processes)\n")
        f.write(f"{'=' * 50}\n\n")
    print(f"\nResults logged to: {log_file}")

# Synchronize all processes
comm.Barrier()

# Only rank 0 collects and writes summary
if rank == 0:
    print(f"\nMPI ring test completed with {n} processes.")
    print(f"Output saved to: {OUTPUT_DIR}")
