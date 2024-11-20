

# Prompt the user to enter the array elements
echo "Enter the elements of the array separated by space:"
read -a array

# Get the length of the array
n=${#array[@]}

# Sorting the array in descending order using Bubble Sort
for ((i = 0; i < n; i++)); do
  for ((j = 0; j < n - i - 1; j++)); do
    if [ ${array[j]} -lt ${array[$((j + 1))]} ]; then
      # Swap elements
      temp=${array[j]}
      array[j]=${array[$((j + 1))]}
      array[$((j + 1))]=$temp
    fi
  done
done

# Display the sorted array
echo "Array elements in descending order: ${array[@]}"  
