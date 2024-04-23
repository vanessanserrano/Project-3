# Spotify Sorter Instructions

## Running the Program

1. **Download** the Spotify Sorter folder.
2. **Execute** `main.exe`:
   - Navigate to the Spotify Sorter folder.
   - Run `main.exe` by double-clicking on it or from the terminal.
3. **Follow** the prompts in the terminal.
4. **Completion**:
   - The program has finished running when you see the "End of program." message.
5. **Rerun**:
   - To rerun the sorter, simply rerun `main.exe`.

## Troubleshooting

### Recompiling `main.exe`

If `main.exe` does not run, you may need to recompile it:

1. **Open a Terminal**:
   - Navigate to the Spotify Sorter folder.
2. **Compile Command**:
   - Run the following command:
     ```
     g++ -o main.exe ./src/main.cpp
     ```
   - This should create `main.exe` in the Spotify Sorter folder, NOT in the `src` folder.
3. **Run the Program**:
   - Execute `main.exe` as described above.

## Note

- **Windows Specific**: The use of `system("pause")` is specific to Windows and may cause undefined behavior on macOS or other non-Windows systems. We recommended running this in an IDE or terminal that supports this command.
