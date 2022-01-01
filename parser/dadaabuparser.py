import sys
import os
import re
import csv

dirname = os.path.abspath(os.path.dirname(__file__))
in_filename = sys.argv[1]
in_dir = sys.argv[2]
out_dir = sys.argv[3]

filenames_to_process = set()


def main():
    with open(in_filename, 'r') as f:
        csvreader = csv.reader(f)
        next(csvreader)

        for id, _, __, ___ in csvreader:
            filenames_to_process.add(id+'.txt')

    files_in_dir = set(os.listdir(in_dir))
    files_to_process = files_in_dir.intersection(filenames_to_process)

    # print(files_in_dir)
    # print(filenames_to_process)
    clean_files(files_to_process, in_dir, out_dir)


def clean_files(files, in_dir, out_dir):
    for file in files:
        # print('Processing file: ' + file)
        if file.endswith(".txt"):
            with open(os.path.join(in_dir, file), "r") as f:
                text = f.read()
                text = clean_text(text)

                with open(os.path.join(out_dir, file), "w") as f_out:
                    f_out.write(text)


def clean_text(text):
    return ' '.join(re.split(r'\W|\d', text))


if __name__ == '__main__':
    main()
    print("Done")
