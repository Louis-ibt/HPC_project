#!/usr/bin/env python3
"""
Helper script to prepare the outputs directory structure
Run this from the project root before executing exercises
"""

from pathlib import Path

def setup_outputs():
    """Create the outputs directory structure"""
    base_dir = Path(__file__).parent
    
    # Directory structure to create
    output_dirs = [
        "outputs/Exercise1_Python",
        "outputs/Exercise2_Parallel_MPI",
        "outputs/Exercise3_CPP",
    ]
    
    for dir_path in output_dirs:
        full_path = base_dir / dir_path
        full_path.mkdir(parents=True, exist_ok=True)
        print(f"✓ {dir_path}/")
    
    print("\nOutputs directory structure ready!")

if __name__ == "__main__":
    setup_outputs()
