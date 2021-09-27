import csv

# Open TSV file for reading
with open("data.tsv", errors='ignore') as titles:

    # Since the file is a TSV file, we can use the CSV reader and change
    # the separator to a tab.
    reader = csv.DictReader(titles, delimiter="\t")

    # Open new CSV file for writing
    with open("shows0.csv", "w", newline='') as shows:

        # Create writer
        writer = csv.writer(shows)

        # Write header of the columns we want
        writer.writerow(["tconst", "primaryTitle", "startYear","endYear", "genres"])

         # Iterate over TSV file
        for row in reader:

            # If non-adult TV show
            if row["titleType"] == "tvSeries" and row["isAdult"] == "0":

                # If year not missing
                if row["startYear"] != "\\N":

                    # If since 1970
                    if int(row["startYear"]) >= 1990:

                        # Write row
                        writer.writerow([row["tconst"], row["primaryTitle"], row["startYear"],row["endYear"], row["genres"]])