import csv

def main():

	# Input and output file paths
	input_file = "merged_everything.csv"
	output_file = "everything2.csv"

	# Read and filter the CSV
	with open(input_file, mode='r') as infile:
		reader = csv.DictReader(infile)
    	# Store records where the last four columns do not equal -1e+34
		valid_records = [
			row for row in reader 
			if not all(float(row[key]) == -1e+34 for key in ['E_WIND', 'N_WIND', 'Z_CURR', 'M_CURR'])
		]

	# Write the filtered data back to a new CSV file
	with open(output_file, mode='w', newline='') as outfile:
		writer = csv.DictWriter(outfile, fieldnames=reader.fieldnames)
		writer.writeheader()
		writer.writerows(valid_records)

	print(f"Filtered records written to {output_file}")



if __name__ == "__main__":
	main()

