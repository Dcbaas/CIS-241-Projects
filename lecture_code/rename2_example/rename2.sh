#/usr/bin/bash


if [ $# -ne 2 ]
then
  echo "Usage: rename2 <oldname> <newname>"
  exit 1
fi

target_name=$2
final_name=$target_name
target_number=0

while [ -f $final_name ]
do
  let target_number++
  final_name=$target_name.$target_number
  echo "$final_name"
done

mv $1 $final_name
