
package main;

import (
        "fmt";
       conv "strconv";
        "os";
        "bufio";
);

func main() {
    var s1, s2 string;
    var inputReader = bufio.NewReader(os.Stdin);
    s1, _ = inputReader.ReadString('\n');
    s2, _ = inputReader.ReadString('\n');
    var birth []int = explode(s1, ',');
    var death []int = explode(s2, ',');
    year := maxAliveYear(birth, death);
    fmt.Println(year);
}

func explode(s string, n rune) []int {
    var v []int = make([]int, 0, len(s));
    var buff string = "";
    for _, c := range s {
        if c != ' ' && c != '"' && c != n && c != '\n' {
            buff += string(c);
        }
        if c == n && buff != "" {
            num, _ := conv.Atoi(buff);
            v = append(v, num);
            //fmt.Println("buff: ", buff);
            buff = "";
        }
    }
    if buff != "" {
        num, _ := conv.Atoi(buff);
        v = append(v, num);
        //fmt.Println("buff: ", buff);
    }
    return v
}

func maxAliveYear(birth []int, death []int) int {
    var arr [102]int = [102]int{0};
    for i, year := range birth {
        arr[year - 1900]++;
        arr[death[i] - 1900 + 1]--;
    }
    var sum, max_sum, year int = 0, 0, -1;
    for i, num := range arr {
        sum += num;
        if sum > max_sum {
            max_sum = sum;
            year = i + 1900;
        }
    }
    if year == -1 && len(birth) > 0 {
        year = 0;
    }
    return year;
}


