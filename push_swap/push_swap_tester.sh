#!/bin/bash

usage() {
    echo "Usage: $0 -nb_test <number_of_tests> -n <number_of_integers> -target <expected_number_of_lines>"
    exit 1
}

if [ $# -lt 6 ]; then
    usage
fi

nb_test=""
n=""
target=""
args_file="args.txt"

while [ $# -gt 0 ]; do
    case $1 in
        -nb_test)
            nb_test=$2
            shift 2
            ;;
        -n)
            n=$2
            shift 2
            ;;
        -target)
            target=$2
            shift 2
            ;;
        *)
            usage
            ;;
    esac
done

if [ -z "$nb_test" ] || [ -z "$n" ] || [ -z "$target" ]; then
    usage
fi
success=0
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

for ((i = 1; i <= nb_test; i++)); do
    args=$(shuf -i 0-200000000 -n $n | tr '\n' ' ')
    output=$(./push_swap $args)
    num_lines=$(echo "$output" | wc -l)
    checker=$(echo "$output" | ./checker_linux $args)
	if [ "$checker" == "OK" ]; then
		if [ "$num_lines" -le "$target" ]; then
			echo -e "${GREEN}TEST $i : $checker : $num_lines"
			((success++))
		else
			echo -e "${RED}TEST $i : $checker: $num_lines"
		fi
    else
        echo -e "TEST $i : ${RED}$checker"
		echo $args > fail
    fi
done

success_percentage=$(echo "scale=2; ($success / $nb_test) * 100" | bc)
echo -e "${GREEN}Percentage of success: $success_percentage%${NC}"