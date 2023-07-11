
package main;

import (
    "fmt";
    "sort";
);

func main() {
    var s string;
    fmt.Scan(&s);
    //fmt.Println(s);
    var ans []string;
    var input []byte = []byte(s);
    sort.Slice(input, func(i, j int) bool { return input[i] < input[j] });
    for {
        ans = append(ans, string(input));
        if !next_permutation(input) {break;}
    }
    fmt.Println(len(ans));
    for _, s := range ans {
        fmt.Println(s);
    }
}

func next_permutation(temp []byte) bool {
    var i, j int;
    var n int = len(temp);
    if n <= 1 {return false;}
    for i = n - 2; i >= 0; i-- {
        if temp[i] < temp[i + 1] {break;}
    }
    if i < 0 {return false;}
    for j = n - 1; j > i; j-- {
        if temp[j] > temp[i] {break;}
    }
    temp[i], temp[j] = temp[j], temp[i];
    //swap(&((*temp)[i]), &((*temp)[j]));
    reverseStringInPlace(temp, i + 1, n - 1);
    return true;
}

func reverseStringInPlace(s []byte, start int, end int) {
    for i, j := start, end; i < j; i, j = i+1, j-1 {
        s[i], s[j] = s[j], s[i]
    }
}
