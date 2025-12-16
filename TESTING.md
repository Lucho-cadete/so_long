
# 🧪 Testing Documentation - so_long

## Overview

Comprehensive testing suite for the so_long project, including map validation tests, memory leak detection, and edge case verification.

---

## 📁 Structure
```
tests/
├── maps/
│   ├── invalid/     # Maps that should be rejected (10 tests)
│   └── valid/       # Maps that should work (4 tests)
├── test_maps.sh     # Automated testing script
└── TESTING.md       # This file
```

---

## 🚀 Quick Start

### Run All Tests (Automated)
```bash
./tests/test_maps.sh
```

Expected output: `14 passed, 0 failed`

### Run Manual Test (Single Map)
```bash
# Invalid map - should show error and exit
./so_long tests/maps/invalid/no_player.ber

# Valid map - should open window
./so_long tests/maps/valid/simple.ber
```

---

## ❌ Invalid Maps (Should Show "Error")

| Test File | Dimensions | What It Tests | Expected Result |
|-----------|------------|---------------|-----------------|
| `empty.ber` | 0×0 | Empty file handling | Error: Empty map |
| `not_rectangular.ber` | Mixed | Different line lengths | Error: Not rectangular |
| `not_closed_top.ber` | 6×5 | Missing top wall | Error: Not closed |
| `no_player.ber` | 6×5 | Missing player (P) | Error: Invalid elements |
| `two_players.ber` | 6×5 | Multiple players | Error: Invalid elements |
| `no_exit.ber` | 6×5 | Missing exit (E) | Error: Invalid elements |
| `no_collectibles.ber` | 6×5 | Missing collectibles (C) | Error: Invalid elements |
| `unreachable_collectible.ber` | 7×5 | C blocked by walls | Error: Invalid path |
| `unreachable_exit.ber` | 8×5 | E blocked by walls | Error: Invalid path |
| `invalid_char.ber` | 6×5 | Contains 'X' | Error: Invalid character |

**Total: 10 test cases**

---

## ✅ Valid Maps (Should Open Window)

| Test File | Dimensions | Description | Difficulty | Elements |
|-----------|------------|-------------|------------|----------|
| `minimal.ber` | 4×4 | Smallest possible valid map | Easy | 1P, 1E, 1C |
| `simple.ber` | 6×5 | Basic map with clear path | Easy | 1P, 1E, 2C |
| `large.ber` | 17×7 | Large map, multiple collectibles | Medium | 1P, 1E, 3C |
| `maze.ber` | 10×7 | Complex pathfinding required | Hard | 1P, 1E, 2C |

**Total: 4 test cases**

---

## 🔍 Memory Leak Testing (Valgrind)

### ⚠️ Important Notes
- Valgrind runs **10-50x slower** than normal execution
- Opening window may take 5-10 seconds
- Analysis after closing may take 10-20 seconds
- **This is completely normal**

### Basic Leak Check
```bash
valgrind --leak-check=full --show-leak-kinds=all \
  ./so_long tests/maps/valid/minimal.ber
```

**What to do:**
1. Wait for window to open (5-10 seconds)
2. Press ESC to close
3. Wait for Valgrind analysis (10-20 seconds)
4. Check output

### Expected Output (SUCCESS)
```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: X allocs, X frees, Y bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### Detailed Leak Check (with origins)
```bash
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./so_long tests/maps/valid/simple.ber
```

### Test Multiple Maps for Leaks
```bash
# Manual approach (recommended)
for map in tests/maps/valid/*.ber; do
    echo "========================================="
    echo "Testing: $(basename $map)"
    echo "========================================="
    echo "Press ESC to close when window opens..."
    valgrind --leak-check=full --error-exitcode=1 \
      ./so_long "$map" 2>&1 | tail -20
    echo ""
done
```

---

## 🎯 Edge Cases Tested

### File Handling
- ✅ Empty file (`empty.ber`)
- ✅ Non-existent file (test manually: `./so_long nonexistent.ber`)

### Map Dimensions
- ✅ Minimum size (4×4 - `minimal.ber`)
- ✅ Small maps (6×5 - `simple.ber`)
- ✅ Large maps (17×7 - `large.ber`)

### Characters
- ✅ All valid: `0`, `1`, `P`, `E`, `C`
- ✅ Invalid characters: `X`, `5`, `A` (`invalid_char.ber`)

### Pathfinding (Flood Fill)
- ✅ Direct path (`minimal.ber`, `simple.ber`)
- ✅ Maze-like paths (`maze.ber`)
- ✅ Unreachable collectible (`unreachable_collectible.ber`)
- ✅ Unreachable exit (`unreachable_exit.ber`)
- ✅ Large connected areas (`large.ber`)

### Element Counts
- ✅ Exactly 1 player (`no_player.ber`, `two_players.ber`)
- ✅ Exactly 1 exit (`no_exit.ber`)
- ✅ At least 1 collectible (`no_collectibles.ber`)

### Map Validation
- ✅ Rectangular shape (`not_rectangular.ber`)
- ✅ Closed by walls (`not_closed_top.ber`)

---

## 📊 Test Results Interpretation

### Automated Script Output

**Success:**
```bash
Testing empty.ber... ✓ PASS (correctly rejected)
Testing minimal.ber... ✓ PASS (window opened)
```

**Failure:**
```bash
Testing no_player.ber... ✗ FAIL (should have been rejected)
Testing simple.ber... ✗ FAIL (validation failed)
```

### Valgrind Output

**✅ No Leaks (GOOD):**
```
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```

**❌ Memory Leak (BAD):**
```
definitely lost: 1,024 bytes in 1 blocks
ERROR SUMMARY: 1 errors from 1 contexts
```

**❌ Invalid Read/Write (BAD):**
```
Invalid read of size 8
Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

---

## 🐛 Debugging Failed Tests

### If Invalid Map Opens Window
**Problem:** Validation not detecting error

**Debug steps:**
1. Check which validation function should catch it
2. Add printf to see what's happening:
```c
printf("DEBUG: Checking player count: %d\n", player_count);
```
3. Run the specific map to see output

### If Valid Map Shows Error
**Problem:** Over-strict validation

**Debug steps:**
1. Note the exact error message
2. Check the map file: `cat tests/maps/valid/problematic.ber`
3. Count elements manually
4. Verify paths are truly reachable

### If Program Crashes (Segmentation Fault)
**Use GDB:**
```bash
gdb --args ./so_long tests/maps/problematic.ber
run
# When it crashes:
bt          # Show backtrace
frame 0     # Go to crash location
print var   # Print variables
```

---

## 🔧 Adding New Tests

### Create Invalid Map
```bash
cat > tests/maps/invalid/my_test.ber << 'EOF'
111111
1P0001
1C0E01
111111
EOF

# Test it
./so_long tests/maps/invalid/my_test.ber
# Should show "Error"
```

### Create Valid Map
```bash
cat > tests/maps/valid/my_test.ber << 'EOF'
111111
1P0C01
100001
1C0E01
111111
EOF

# Test it
./so_long tests/maps/valid/my_test.ber
# Should open window
```

### Re-run Full Suite
```bash
./tests/test_maps.sh
```

---

## ✅ Pre-Submission Checklist

Before considering the project complete:

### Functionality
- [ ] All 10 invalid maps properly rejected
- [ ] All 4 valid maps open window
- [ ] Player moves with W/A/S/D
- [ ] ESC closes window properly
- [ ] Collectibles disappear when collected
- [ ] Exit opens when all collectibles gathered
- [ ] Victory message displays
- [ ] Move counter works

### Quality Assurance
- [ ] No memory leaks (Valgrind clean on all valid maps)
- [ ] No segmentation faults
- [ ] No crashes with any test map
- [ ] Handles non-existent files gracefully

### Code Standards
- [ ] Norminette passes on all `.c` and `.h` files
- [ ] No forbidden functions used
- [ ] Makefile works: `make`, `make clean`, `make fclean`, `make re`
- [ ] No relinks on repeated `make`

### Documentation
- [ ] README.md updated
- [ ] Testing documented
- [ ] Code commented where necessary

---

## 📚 Commands Reference

### Testing
```bash
# Quick functional test
./tests/test_maps.sh

# Manual test single map
./so_long tests/maps/valid/simple.ber

# Memory leak check
valgrind --leak-check=full ./so_long tests/maps/valid/minimal.ber
```

### Compilation
```bash
make          # Compile
make clean    # Remove objects
make fclean   # Remove objects + executable
make re       # Recompile from scratch
```

### Code Quality
```bash
# Check norm
norminette *.c *.h

# Check for leaks (detailed)
valgrind --leak-check=full --show-leak-kinds=all \
  --track-origins=yes ./so_long maps/test.ber
```

---

## 🎓 Testing Best Practices

1. **Test early, test often** - Don't wait until the end
2. **Fix leaks immediately** - They compound quickly
3. **Add tests for bugs** - When you fix a bug, add a test
4. **Use Valgrind regularly** - Even if it's slow
5. **Keep test maps simple** - Easy to understand = easy to debug

---

## 📚 Resources

- [Flood-Fill logic](https://geeksforgeeks.org)
- [Valgrind Quick Start](https://valgrind.org/docs/manual/quick-start.html)
- [GDB Tutorial](https://www.gnu.org/software/gdb/documentation/)
- [Writing Good Tests](https://42-cursus.gitbook.io/)


### Known Issues (Not Our Bugs)

Valgrind reports ~270KB of "definitely lost" memory coming from:
- `glfwCreateWindow` (GLFW library)
- Internal graphics library allocations

**These are NOT leaks from our code.** They come from external 
graphics libraries (GLFW/MLX42) and are accepted in 42 graphic projects.

**Proof:** All mallocs in our code (map, textures, game struct) 
are properly freed. Original leak from `load_textures` (48 bytes) 
was fixed by adding `free(textures)` before `mlx_terminate`.

----

**Last Updated:** December 2024  
**Project:** so_long (42 Network)  
**Author:** Luis Martinez  
**Verified:** All commands tested and working ✅