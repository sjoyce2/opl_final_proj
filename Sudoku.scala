object Sudoku extends App {
  def readInput(i: Int, puzzle: Array[Array[Int]]) : Array[Array[Int]] = {
    var line = scala.io.StdIn.readLine("Enter line number " + (i + 1) + " of the sudoku.");
    while (line.length() != 9) {
      println("That line is the wrong length!");
      line = scala.io.StdIn.readLine("Enter line number " + (i + 1) + " of the sudoku.");
    }
    var lineArr = line.split("");
    try {
      var numArr = new Array[Int](9);
      for (j <- 0 to 8) {
        var newNum = lineArr(j).toInt;
        numArr(j) = newNum;
      }
      puzzle(i) = numArr;
      if (i < 8) {
        readInput(i + 1, puzzle);
      }
      return puzzle;
    } catch {
      case nfe: NumberFormatException => {
        println("You didn't enter all numbers! Now we have to start over!");
        readInput(0, puzzle);
      }
    }
  }

  //there is probably a faster way to check this. Something with another multidimensional array?
  //not sure if that would actually be faster though...
  def checkIfValid(array: Array[Array[Int]]): Boolean = {
    var invalidVal = false;
    for (i <- 0 to 8) {
      var usedNums = new Array[Int](9);
      for (j <- 0 to 8) {
        var currVal = array(i)(j);
        if (currVal != 0 && usedNums.contains(currVal)) {
          println("Invalid value in row " + (i + 1) + ", column " + (j + 1));
          invalidVal = true;
        } else {
          usedNums(j) = currVal;
        }
      }
    }
    for (j <- 0 to 8) {
      var usedNums = new Array[Int](9);
      for (i <- 0 to 8) {
        var currVal = array(i)(j);
        if (currVal != 0 && usedNums.contains(currVal)) {
          println("Invalid value in row " + (i + 1) + ", column " + (j + 1));
          invalidVal = true;
        } else {
          usedNums(j) = currVal;
        }
      }
    }
    return invalidVal;
  }

  def solvePuzzle(): Unit = {
    var line = "";
    var puzzle = Array.ofDim[Int](9, 9);
    println("You will be entering the values of the unfinished sudoku puzzle, line by line. Enter" +
      " in a zero (0) character to\n signify an empty space.");
    puzzle = readInput(0, puzzle);

    if (checkIfValid(puzzle)) {
      println("That was an invalid puzzle, try again!");
      solvePuzzle();
    } else {
      // TODO: solve(puzzle);
    }
  }

  solvePuzzle();
}
