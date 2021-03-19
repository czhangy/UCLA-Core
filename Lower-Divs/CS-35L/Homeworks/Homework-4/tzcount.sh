#!/bin/bash

git log | grep -E '^Date:.*[+-][0-9]{4}$' | grep -Eo [+-][0-9]{4} | sort -n | uniq -c | sed -E 's/(.*) (.*)/\2 \1/g'
