#!/bin/bash
# filepath: /home/cloe/42Project/philosophers/philo/tester.sh

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Function to print test header
print_header() {
    echo -e "\n${YELLOW}=== Test $1: $2 ===${NC}"
}

# Function to check death timing
check_death_timing() {
    local expected=$1
    local tolerance=50  # 50ms tolerance
    local death_time=$(./philo $2 $3 $4 $5 2>/dev/null | grep "died" | cut -d' ' -f1 | sed 's/ms//')
    
    if [ -z "$death_time" ]; then
        echo -e "${RED}❌ No death detected${NC}"
        return 1
    fi
    
    if [ $death_time -ge $((expected - tolerance)) ] && [ $death_time -le $((expected + tolerance)) ]; then
        echo -e "${GREEN}✓ Death timing correct: ${death_time}ms${NC}"
        return 0
    else
        echo -e "${RED}❌ Wrong death timing: ${death_time}ms (expected ~${expected}ms)${NC}"
        return 1
    fi
}

# Basic tests
print_header "1" "Basic no-death test (4 410 200 200)"
timeout 3s ./philo 4 410 200 200 > /dev/null 2>&1
if [ $? -eq 124 ]; then
    echo -e "${GREEN}✓ No philosopher died (as expected)${NC}"
else
    echo -e "${RED}❌ Test failed - unexpected death${NC}"
fi

# Death timing tests
print_header "2" "Death timing test (4 310 200 100)"
check_death_timing 310 4 310 200 100

# One philosopher test
print_header "3" "Single philosopher test"
check_death_timing 800 1 800 200 200

# Meal count test
print_header "4" "Meal count test (5 800 200 200 7)"
result=$(./philo 5 800 200 200 7 2>/dev/null | grep "is eating" | wc -l)
