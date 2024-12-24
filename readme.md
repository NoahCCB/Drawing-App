## Usage Guide

### Basic Drawing
1. Launch the application
2. Left-click and drag to draw
3. Release to stop drawing

### Customizing Drawing Tools
- **Change Pen Color**: Options → Pen Color
- **Adjust Pen Width**: Options → Pen Width (1-50 pixels)

### File Operations
- **New Drawing**: Options → Clear Screen (Ctrl+L)
- **Open Image**: File → Open
- **Save Drawing**: File → Save As → Select Format
- **Print**: File → Print

### Keyboard Shortcuts
- Open: System default (Ctrl+O on Windows/Linux, Cmd+O on macOS)
- Clear Screen: Ctrl+L
- Exit: System default (Alt+F4 on Windows/Linux, Cmd+Q on macOS)

## Architecture

### Design Pattern
The application follows the Qt widget-based architecture pattern with:
- Main window as the container (`QMainWindow`)
- Custom widget for drawing (`QWidget`)
- Event-driven interaction model

### File Format Support
Supports all image formats provided by Qt, including:
- PNG
- JPEG
- BMP
- Other formats supported by the Qt image I/O system

## License
None

## Author
Noah Cunningham Baker

## Troubleshooting
- If the application fails to start, ensure Qt libraries are properly installed
- For printing issues, verify Qt PrintSupport module is available
- For file saving issues, check write permissions in the target directory

