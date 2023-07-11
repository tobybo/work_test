
package main;

import (
    "fmt";
);

func main() {
    A, B := 0, 0
    fmt.Scan(&A, &B);
    fmt.Print(multiply(A, B), "\n");
}

func multiply(A int, B int) (ans int) {
    for B > 0 {
        if B & 1 == 1 {
            ans += A;
        }
        B >>= 1;
        A <<= 1;
    }
    return
}

