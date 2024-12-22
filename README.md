# Interactive Periodic Table

A C++ implementation of an interactive periodic table using the graphics.h library. The project consists of two main components: a data entry system and an interactive viewer.

## Features

- **Interactive Graphical Interface**

  - Visual representation of the periodic table
  - Color-coded element categories
  - Element information display panel
  - Search functionality
  - Animated text effects

- **Element Information**

  - Atomic number
  - Element name and symbol
  - Category/Group classification
  - Group and Period numbers
  - Electronic configuration
  - Melting and boiling points
  - Atomic mass
  - Oxidation states

- **Search Capabilities**
  - Search by element name
  - Search by element symbol
  - Search by atomic number

## Project Structure

### Files

1. **PER_TABL.CPP**

   - Main application file
   - Handles the graphical interface
   - Implements search and display functionality
   - Contains the periodic table visualization

2. **CHEM_DBA.CPP**

   - Database management utility
   - Used for adding new elements to the database
   - Creates and updates the binary data file

3. **CBASE.BIN**
   - Binary file storing element data
   - Contains information for up to 110 elements
   - **Warning**: Do not edit manually

## Technical Requirements

- C++ compiler with graphics.h support
- DOS/Windows environment (due to graphics.h dependency)
- Minimum 640x480 display resolution

## Usage

### Viewing the Periodic Table

1. Compile and run `PER_TABL.CPP`
2. Use arrow keys to navigate the menu
3. Press Enter to select options
4. Press Backspace to return to previous screens

### Adding New Elements

1. Compile and run `CHEM_DBA.CPP`
2. Enter the element details as prompted
3. Data will be automatically saved to CBASE.BIN

### Search Function

1. Select "Chemical Analyser" from the main menu
2. Enter element name, symbol, or atomic number
3. Press Enter to search
4. View detailed element information

## Menu Options

1. **Periodic Table**

   - View the complete periodic table
   - Color-coded element categories
   - Interactive element selection

2. **Chemical Analyser**

   - Search functionality
   - Detailed element information display
   - Electronic configuration visualization

3. **Exit**
   - Safely exit the application

## Notes

- The project uses a binary file system for data storage
- Maximum supported elements: 110
- Color coding helps identify element categories
- Electronic configurations are displayed using standard notation
- The interface includes helpful navigation hints

## Warnings

- Do not modify CBASE.BIN directly
- Use CHEM_DBA.CPP only for adding new elements
- Backup CBASE.BIN before making any changes

## Technical Details

- Uses graphics.h for GUI
- Implements inheritance for element display classes
- Binary file I/O for data persistence
- Custom animation effects for text display
