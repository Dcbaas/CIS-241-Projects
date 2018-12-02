#/usr/bin/bash


if [ $# -ne 2 ]
then
  echo "Usage: rename2 <oldname> <newname>"
  exit 1
fi

target_name=$2
final_name=$target_name
target_number=0

if [ -f $1 ]
then
  while [ -f $final_name ]
  do
    let target_number++
    final_name=$target_name.$target_number
  done

  mv $1 $final_name
else
  echo "$1 does not exist"
  exit 1
fi
