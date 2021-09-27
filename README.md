# BingeHacker v1.0

# Authors
Miguel Caputo, Juan Gonzalez, and Nathan Whelden

## Description:

This program is designed to provide information on TV series. The program lets you, the user, choose between two different data structures (AVL Tree or Map) to store this information and will provide you with the run time of each data structure, as well as the option to switch between them. The information you will find here will be the name of the TV series, the IMDb ID code, the start and end year, and the genres. The program will allow you to search for TV series by name, by keyword, or randomly search for a TV series. This program also has an additional feature which will take you directly to the IMDb webpage of the TV series being displayed if you choose to do so. For a video demonstration of this program and its features please visit the following link: https://youtu.be/cYSQ_O3vyFk

The clean_database.py included was used to reformat the IMDb dataset from a .tsv into a .csv, and trimmed the original data to 146,000 tuples by only including TV series created after 1989.

## Instructions:
Begin by downloading  file named BingeHacker.cpp Open your computer's command-line interface. Make sure you are in the source folder directory and then type the following command:

```g++ BingeHacker.cpp -o BingeHacker```

This command should have created a new executable called BingeHacker.exe in the source folder. To run the program, enter ./BingeHacker in the command-line, or launch the executable that was created in the directory.

Note: If your computer uses the Windows OS, you will need a GNU c++ compiler. You may need to use the PowerShell command-line interface in order to run the program.

**The program should show you a main menu with 3 options:**

1. Save the data of the shows using a Map Structure.
2. Save the data of the shows using an AVL Tree Structure.
3. Exit the program.

- If you input option 1 or 2, the program will load the data in the shows.txt file to the corresponding data structure.
- If you input option 3, the program will terminate.

After inputting option 1 or 2, the program will show you a search menu with 5 options:
1. Search for a show by name.
2. Search for multiple shows by a keyword.
3. Find a random show.
4. Change the data structure used.
5. Exit the program.

- If you input option 1, the program will prompt you to input the name of the show. If the TV show is found, the program will ask if you would like to go to the IMDb website for the show and will show you a menu with 2 options:
    1.Yes
    2. No
    - If you input option 1, the program will open your browser and take you to the website of that show.
    - If you input option 2, the program will take you back to the search menu.
- If you input option 2, the program will prompt you to input the keyword for your search.
- If you input option 3, the program will find a random show for you. Then the program will ask if you would like to go to the IMDB website for the show and will show you a menu with 2 options:
    1.Yes
    2. No
    - If you input option 1, the program will open your browser and take you to the website of that show.
    - If you input option 2, the program will take you back to the search menu.
- If you input option 4, the program will take you back to the main menu.
- If you input option 5, the program will terminate.

We hope you enjoyed using BingeHacker v1.0!



