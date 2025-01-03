def sum_m(lst):
    max_i = 0
    max_j = 0
    max_sum = 0

    for i in range(len(lst)):
        current_sum = 0
        for j in range(i, len(lst)):
            current_sum += lst[j]
            if current_sum > max_sum:
                max_sum = current_sum
                max_i = i
                max_j = j

    return max_sum, max_i, max_j

if __name__ == "__main__":
    lst = [1, -2, 1, 2, -1, 3, -2, 1]
    max_sum, max_i, max_j = sum_m(lst)
    print(f"Max sum: {max_sum}, from index {max_i} to {max_j}")