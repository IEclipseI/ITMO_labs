import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;

public class N19_1 {
    static boolean isGood(String bracket){
        //System.out.println(bracket);
        Stack<Character> st = new Stack<Character>();
        for (int i = 0; i < bracket.length(); i++) {
            if (st.empty()) {
                st.push(bracket.charAt(i));
            } else {
                if (bracket.charAt(i) == ']' && st.peek() == '[' ||
                        bracket.charAt(i) == ')' && st.peek() == '(') {
                    st.pop();
                } else {
                    st.push(bracket.charAt(i));
                }
            }
        }
        for (char i : st
                ) {
            if (i == ']' || i == ')') {
                return false;
            }
        }
        return true;
    }
    static long countPrefix(String bracket, int n) {
        if (!isGood(bracket)) {
            return 0;
        }
        long[][] dp = new long[n + 1][n + 1];
        int balance = 0;
        for (int i = 0; i < bracket.length(); i++) {
            if (bracket.charAt(i) == '(' || bracket.charAt(i) == '[') {
                balance++;
            } else {
                balance--;
            }
        }
        if (balance < 0) {
            return 0;
        }
        dp[bracket.length()][balance] = 1;
        for (int i = bracket.length() + 1; i < n + 1; i++) {
            for (int j = 0; j < n; j++) {
                if (j != 0) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
                } else {
                    dp[i][j] = dp[i - 1][j + 1];
                }
            }
        }
        return (long)(dp[n][0] * Math.pow(2, ((double)n - balance  - bracket.length())/2));
    }
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("num2brackets2.in"));
        PrintWriter out = new PrintWriter(new File("num2brackets2.out"));
        int n = (int)in.nextInt() * 2;
        long numb = in.nextInt();
        String answer = "";
        char[] ar = {'(', ')', '[',']'};
        //System.out.println(countPrefix("", 8));
        //System.out.println(countPrefix("", 8));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                //System.out.println(answer + ar[j] + " " + countPrefix(answer + ar[j], n));
                if (countPrefix(answer + ar[j], n) > numb) {
                    answer += ar[j];
                    //System.out.println(answer);
                    break;
                } else {
                    numb -= countPrefix(answer + ar[j], n);
                }
            }
        }
        out.print(answer);
        out.close();
    }
    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        FastScanner(File f) {
            try {
                br = new BufferedReader(new FileReader(f));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }

        String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        long nextInt() {
            return Long.parseLong(next());
        }
    }
}