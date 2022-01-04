#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int getBits(int dec) {
  // Returns the number of bits the binary equivalent of a decimal will contain
  int bits = 0;
  int temp = dec;

  while (temp != 0) {
    temp /= 2;
    bits++;
  }

  return bits;
}

int* decimalToBinary(int dec) {
  // Returns a malloc array containing the binary equivalent of a decimal value
  int bits = getBits(dec);
  int* bin = (int*) malloc((getBits(dec) + 1) * sizeof(int));

  bin[0] = bits;

  int decimal = dec;
  int temp = decimal;
  int count = 1;

  while(temp != 0) {
    *(bin + count) = (decimal % 2);
    decimal /= 2;
    temp /= 2;
    count++;
  }

  return bin;
}

int binaryToDecimal(int* bin) {
  // Returns the integer equivalent to a binary value
  int dec = 0;
  int* binary = bin;

  int val;
  int bits = bin[0];

  for (int i = binary[0]; i > 0; i--) {
      val = binary[i];
      if (i == 1) {
        dec += val;
      } else {
        dec = (dec + val) * 2;
      }
  }

  return dec;
}

int add(int* arg0, int* arg1) {
  int* bin0 = arg0;
  int* bin1 = arg1;
  int* res;

  int carryin = 0;
  if (bin0[0] >= bin1[0]) {
    res = (int*) malloc((bin0[0] + 2) * sizeof(int));
    res[0] = (bin0[0] + 1);
    for (int i = 1; i <= bin0[0]; i++) {
      if (carryin == 0) {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin0[i];
        }
      } else {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin0[i] == 0) {
            res[i] = 1;
          } else if (bin0[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  } else {
    res = (int*) malloc((bin1[0] + 2) * sizeof(int));
    res[0] = (bin1[0] + 1);
    for (int i = 1; i <= bin1[0]; i++) {
      if (carryin == 0) {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin1[i];
        }
      } else {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin1[i] == 0) {
            res[i] = 1;
          } else if (bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  }
  res[res[0]] = carryin;

  return binaryToDecimal(res);
}

int* subtractDIV(int* arg0, int* arg1) {
  int max;

  if (arg0[0] >= arg1[0]) {
    max = arg0[0];
  } else {
    max = arg1[0];
  }

  int* bin0 = (int*) malloc((max + 1) * sizeof(int));
  int* bin1 = (int*) malloc((max + 1) * sizeof(int));
  bin0[0] = max;
  bin1[0] = max;

  for (int i = 1; i <= max; i++) {
    if (i <= arg0[0]) {
      bin0[i] = arg0[i];
    } else {
      bin0[i] = 0;
    }

    if (i <= arg1[0]) {
      if (arg1[i] == 1) {
        bin1[i] = 0;
      } else if (arg1[i] == 0) {
        bin1[i] = 1;
      }
    } else {
      bin1[i] = 1;
    }
  }

  bin1 = decimalToBinary(add(bin1, decimalToBinary(1)));

  int carryin = 0;
  int* res;
  if (bin0[0] >= bin1[0]) {
    res = (int*) malloc((max + 1) * sizeof(int));
    res[0] = max;
    for (int i = 1; i <= bin0[0]; i++) {
      if (carryin == 0) {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin0[i];
        }
      } else {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin0[i] == 0) {
            res[i] = 1;
          } else if (bin0[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  } else {
    res = (int*) malloc((max + 1) * sizeof(int));
    res[0] = max;
    for (int i = 1; i <= bin1[0]; i++) {
      if (carryin == 0) {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin1[i];
        }
      } else {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin1[i] == 0) {
            res[i] = 1;
          } else if (bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  }

  return res;
}

int* addDIV(int* arg0, int* arg1) {
  int* bin0 = arg0;
  int* bin1 = arg1;
  int* res;

  int carryin = 0;
  if (bin0[0] >= bin1[0]) {
    res = (int*) malloc((bin0[0] + 1) * sizeof(int));
    res[0] = bin0[0];
    for (int i = 1; i <= bin0[0]; i++) {
      if (carryin == 0) {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin0[i];
        }
      } else {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin0[i] == 0) {
            res[i] = 1;
          } else if (bin0[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  } else {
    res = (int*) malloc((bin1[0] + 1) * sizeof(int));
    res[0] = bin1[0];
    for (int i = 1; i <= bin1[0]; i++) {
      if (carryin == 0) {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin1[i];
        }
      } else {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin1[i] == 0) {
            res[i] = 1;
          } else if (bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  }

  return res;
}

int subtract(int* arg0, int* arg1) {
  int max;

  if (arg0[0] >= arg1[0]) {
    max = arg0[0];
  } else {
    max = arg1[0];
  }

  int* bin0 = (int*) malloc((max + 1) * sizeof(int));
  int* bin1 = (int*) malloc((max + 1) * sizeof(int));
  bin0[0] = max;
  bin1[0] = max;

  for (int i = 1; i <= max; i++) {
    if (i <= arg0[0]) {
      bin0[i] = arg0[i];
    } else {
      bin0[i] = 0;
    }

    if (i <= arg1[0]) {
      if (arg1[i] == 1) {
        bin1[i] = 0;
      } else if (arg1[i] == 0) {
        bin1[i] = 1;
      }
    } else {
      bin1[i] = 1;
    }
  }

  bin1 = decimalToBinary(add(bin1, decimalToBinary(1)));

  int carryin = 0;
  int* res;
  if (bin0[0] >= bin1[0]) {
    res = (int*) malloc((max + 1) * sizeof(int));
    res[0] = max;
    for (int i = 1; i <= bin0[0]; i++) {
      if (carryin == 0) {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin0[i];
        }
      } else {
        if (bin1[i] == 0 || bin1[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin0[i] == 0) {
            res[i] = 1;
          } else if (bin0[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  } else {
    res = (int*) malloc((max + 1) * sizeof(int));
    res[0] = max;
    for (int i = 1; i <= bin1[0]; i++) {
      if (carryin == 0) {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 0;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 1;
            carryin = 0;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        } else {
          res[i] = bin1[i];
        }
      } else {
        if (bin0[i] == 0 || bin0[i] == 1) {
          if (bin0[i] == 0 && bin1[i] == 0) {
            res[i] = 1;
            carryin = 0;
          } else if ((bin0[i] == 0 && bin1[i] == 1) || (bin0[i] == 1 && bin1[i] == 0)) {
            res[i] = 0;
            carryin = 1;
          } else if (bin0[i] == 1 && bin1[i] == 1) {
            res[i] = 1;
            carryin = 1;
          }
        } else {
          if (bin1[i] == 0) {
            res[i] = 1;
          } else if (bin1[i] == 1) {
            res[i] = 0;
            carryin = 1;
          }
        }
      }
    }
  }

  if (binaryToDecimal(arg1) > binaryToDecimal(arg0)) {
    for (int i = 1; i <= res[0]; i++) {
      if (res[i] == 0) {
        res[i] = 1;
      } else if (res[i] == 1){
        res[i] = 0;
      }
    }
    return add(res, decimalToBinary(1));
  }

  return binaryToDecimal(res);
}

int multiply(int* arg0, int* arg1) {
  int* multiplicand = arg0;
  int* multiplier = arg1;
  int* product = (int*) malloc(9 * sizeof(int));
  int prev;

  for (int i = multiplicand[0] + 1; i <= 8; i++) {
    multiplicand[i] = 0;
  }
  multiplicand[0] = 8;

  for (int l = 0; l < 8; l++) {
    if (multiplier[1] == 0) {
      for (int i = multiplicand[0]; i >= 1; i--) {
        if (i == 1) {
          prev = 0;
        } else {
          prev = multiplicand[i - 1];
        }
        multiplicand[i] = prev;
      }

      for (int i = 1; i <= multiplier[0]; i++) {
        if (i == multiplier[0]) {
          prev = 0;
        } else {
          prev = multiplier[i + 1];
        }
        multiplier[i] = prev;
      }
    } else if (multiplier[1] == 1) {
      product = decimalToBinary(add(multiplicand, product));

      for (int i = multiplicand[0]; i >= 1; i--) {
        if (i == 1) {
          prev = 0;
        } else {
          prev = multiplicand[i - 1];
        }
        multiplicand[i] = prev;
      }

      for (int i = 1; i <= multiplier[0]; i++) {
        if (i == multiplier[0]) {
          prev = 0;
        } else {
          prev = multiplier[i + 1];
        }
        multiplier[i] = prev;
      }
    }
  }

  return binaryToDecimal(product);
}

int divide(int* arg0, int* arg1) {
  int* q = arg0;
  int* m = arg1;
  int* a = (int*) malloc((q[0] + 2) * sizeof(int));
  a[0] = q[0] + 1;

  for (int i = 1; i <= a[0]; i++) {
    a[i] = 0;
  }

  for (int i = 0; i < q[0]; i++) {
    int prev = 0;
    for (int i = a[0]; i >= 1; i--) {
      if (i == 1) {
        prev = q[q[0]];
      } else {
        prev = a[i - 1];
      }
      a[i] = prev;
    }

    a = subtractDIV(a, m);

    if (a[a[0]] == 1) {
      for (int i = a[0]; i >= 1; i--) {
        if (i == 1) {
          prev = 0;
        } else {
          prev = q[i - 1];
        }
        q[i] = prev;
      }
      a = addDIV(a, m);
    } else if (a[a[0]] == 0) {
      for (int i = a[0]; i >= 1; i--) {
        if (i == 1) {
          prev = 1;
        } else {
          prev = q[i - 1];
        }
        q[i] = prev;
      }
    }
  }

  return binaryToDecimal(q);
}
