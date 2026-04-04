# MPI Setup Guide

## Problem: `RuntimeError: cannot load MPI library`

On Windows, `mpi4py` requires the **Microsoft MPI (MSMPI)** runtime to be installed.

## Solution

### 1. **Install Microsoft MPI**

Download and install both files from:  
**https://www.microsoft.com/en-us/download/details.aspx?id=57467**

- `msmpisdk.msi` – SDK (development files)
- `msmpisetup.exe` – Runtime

### 2. **Install mpi4py** (if not already done)

```powershell
pip install mpi4py
```

### 3. **Restart** your system (important!)

### 4. **Test the installation**

```powershell
# Run the MPI ring with 4 processes
mpiexec -n 4 python Exercise1_Parallel_MPI/3_communication_ring/mpi_ring.py
```

---

## Alternative: Linux/macOS

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install libopenmpi-dev openmpi-bin
pip install mpi4py
```

### macOS
```bash
brew install open-mpi
pip install mpi4py
```

---

## Useful Commands

```powershell
# Check MPI version
mpiexec --version

# Run with N processes
mpiexec -n 8 python script.py

# Check if mpi4py is properly installed
python -c "from mpi4py import MPI; print('✓ MPI OK')"
```

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| `ModuleNotFoundError: No module named 'mpi4py'` | `pip install mpi4py` |
| `RuntimeError: cannot load MPI library` | Install Microsoft MPI and restart |
| `mpiexec: command not found` | Restart system after MSMPI installation |
| Script runs as single process | Use `mpiexec -n N python script.py` (not `python`) |
