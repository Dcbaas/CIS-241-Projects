#!/bin/bash

input="classes"
while read -r line1 line2
do
  mkdir -p $line1
  touch $line1/$line2
  
done <"$input"
