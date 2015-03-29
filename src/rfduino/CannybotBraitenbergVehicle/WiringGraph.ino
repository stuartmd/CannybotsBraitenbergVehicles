//////////////////////////////////////////////////////////////////////////////////////////////////
//
// Cannybots Blue Brain - Braitenberg Vehicle Demonstration
// Handles internal wiring diagrams defining Braitenberg Vehicle behaviour
//
// Authors:  Stuart Dickson
//
// License: http://opensource.org/licenses/MIT
//
// Version:   1.0  -  28.03.2015  -  Initial commit  (stuartmd@hoardingshinies.com)
//////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Returns the required output value by looking up the response curve.
 *
 * The response-curve is defined as an array of ints.
 * curve[0] stores the number of points on the graph, N.
 * 		N _must_ be >1
 * Where i is the index of the nth tuple input/output
 * 	 curve[2*i+1] is the input
 *   curve[2*i+2] is the output
 * A linear relationship between pairs of points is
 * Where val lies between two points, the desired output is calculated by
 * linear interpolation
 *
 *  e.g. simple threshold
 *     [2, 512, 0, 513, 255]
 */
int apply_response_curve(const int& val, int* curve) {
  int i, il;

  if (val < curve[1]) {
    return curve[2];
  } else if (val >= (curve[ curve[0]*2-1 ])) {
    return curve[ curve[0]*2 ];
  } else {
    for(i=1, il=curve[0]*2; i<il; i+=2) {
      if (val >= curve[i] && val < curve[i+2]) {
        return (val-curve[i]) * ((float)(curve[i+3] - curve[i+1]) / (float)(curve[i+2] - curve[i])) + curve[i+1];
      }
    }
  }
}
