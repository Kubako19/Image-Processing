The program was written for the needs of the Basic Programming course at the Wrocław University of Science and 
Technology at field of Automation and Robotics.

# Program for PGM and PPM image processing
### Available filters in program:
* negative,
* contouring,
* thresholding (also thresholding whites and blacks),
* horizontal or vertical blur,
* histogram.

## Executing program
### Executing program with arguments
Syntax for program call options:

`program [-i name of image] [options of image processing] [-o name of result file] [-d]`.

It is important to put these arguments in the correct order. It will depend on what the resulting image will look like.
The first option should be `[-i image name]`. In the case of a **PPM** image, the next option should be `[-m color]`. 
It allows you to choose the color on which the operations will be performed, and if you specify the `s` option after it,
 a conversion to gray will be done. The file after such conversion should be saved in **PGM** format.

Available options for color processing:
* `[ r ]` - processing of red color,
* `[ g ]` - processing of green color,
* `[ b ]` - processing of blue color,
* `[ w ]` - processing of all colors at once,
* `[ s ]` - conversion to grey scale.

When you execute a program with a **PGM** image, you do not need to specify the `[-m]` option.

Available options for image processing:
* `[ -n ]` - negative filter,
* `[ -k ]` - contouring filter,
* `[ -t value ]` - thresholding filter,
* `[ -tb value ]` - thresholding blacks filter,
* `[ -tw value ]` - thresholding whites filter,
* `[ -x ]` - horizontal blur filter,
* `[ -y ]` - vertical blur filter,
* `[ -h ]` - histogram filter.

Finally, the option `[-o name of the result file]` should be given. It can be followed by the option `[-d]`, 
which will display the loaded and resulting image.

#### Example of executing program
**PPM image**:  
`./ImagesProcessing -i kubus.ppm -m r -n -k -o kubus_result.ppm -d`

**PPM image with conversion**:  
`./ImagesProcessing -i kubus.ppm -m s -n -k -o kubus_result.pgm -d`

**PGM image**:  
`./ImagesProcessing -i kubus.pgm -n -k -o kubus_result.pgm -d`

### Executing program without arguments
If no program arguments are given, the context menu will be displayed. It shows the available options and guides you 
through the entire program.