#!/bin/bash

for i in  {1..30}
do
	val=$(shuf -i 1-20 -n 1)
	echo "$val"
done
