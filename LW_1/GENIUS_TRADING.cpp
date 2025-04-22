x, y = map(int, input().split())
total_count = 0


for a_len in range(1, 60):
    for b_len in range(1, 60):
        for c_len in range(1, 60):
            
            binary_rep = "1" * a_len + "0" * b_len + "1" * c_len
            
            
            if len(binary_rep) > 63:  
                continue

            
            decimal_value = int(binary_rep, 2)

            
            if x <= decimal_value <= y:
                total_count += 1 


print(total_count)

