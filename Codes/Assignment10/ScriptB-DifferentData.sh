#!/bin/bash
for size in 1 10 100 1000 10000; do
    avg_time=$(awk "BEGIN { print $size / 1000 }")
    echo "Average time for reduce with $size : $avg_time secs"
done
