#!/bin/bash

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

EXECUTABLE="./so_long"
PASSED=0
FAILED=0

echo "════════════════════════════════════════"
echo "   🧪 SO_LONG AUTOMATED TESTING"
echo "════════════════════════════════════════"
echo ""

# Test mapas inválidos (deben fallar)
echo -e "${YELLOW}Testing INVALID maps (should show Error):${NC}"
echo "----------------------------------------"

for map in tests/maps/invalid/*.ber; do
    if [ -f "$map" ]; then
        echo -n "Testing $(basename $map)... "
        
        # Ejecutar y capturar salida
        output=$($EXECUTABLE "$map" 2>&1)
        exit_code=$?
        
        # Debe salir con error (exit code != 0) o mostrar "Error"
        if [ $exit_code -ne 0 ] || echo "$output" | grep -q "Error"; then
            echo -e "${GREEN}✓ PASS${NC} (correctly rejected)"
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC} (should have been rejected)"
            ((FAILED++))
        fi
    fi
done

echo ""
echo -e "${YELLOW}Testing VALID maps (should NOT show Error):${NC}"
echo "----------------------------------------"

# Test mapas válidos (NO deben fallar en validación)
for map in tests/maps/valid/*.ber; do
    if [ -f "$map" ]; then
        echo -n "Testing $(basename $map)... "
        
        # Ejecutar solo validación (timeout 2s para que no se quede abierto)
        timeout 2s $EXECUTABLE "$map" > /dev/null 2>&1 &
        pid=$!
        sleep 0.5
        
        # Verificar si el proceso sigue corriendo (bueno) o murió (malo)
        if kill -0 $pid 2>/dev/null; then
            echo -e "${GREEN}✓ PASS${NC} (window opened)"
            kill $pid 2>/dev/null
            ((PASSED++))
        else
            echo -e "${RED}✗ FAIL${NC} (validation failed)"
            ((FAILED++))
        fi
    fi
done

echo ""
echo "════════════════════════════════════════"
echo -e "Results: ${GREEN}$PASSED passed${NC}, ${RED}$FAILED failed${NC}"
echo "════════════════════════════════════════"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}🎉 All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}❌ Some tests failed${NC}"
    exit 1
fi
