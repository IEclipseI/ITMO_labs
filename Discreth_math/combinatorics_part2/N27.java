import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N27 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextbrackets.in"));
        PrintWriter out = new PrintWriter(new File("nextbrackets.out"));
        StringBuilder sb = new StringBuilder(in.next());
        int n = sb.length();
        int balance = 0;
        while (balance < 2  && sb.length() > 0 || sb.charAt(sb.length() - 1)  == ')') {
            if (sb.charAt(sb.length() - 1) == ')') {
                balance++;
                sb.deleteCharAt(sb.length() - 1);
            } else {
                balance--;
                sb.deleteCharAt(sb.length() - 1);
            }
            if (sb.length() == 0) {
                out.print("-");
                out.close();
                return;
            }
        }
        sb.setCharAt(sb.length() - 1, ')');
        balance -= 2;
        int size = sb.length(); 
        for (int i = 0; i < (n - size - balance) / 2; i++) {
            sb.append('(');
        }
        for (int i = 0; i < (n - size - balance) / 2; i++) {
            sb.append(')');
        }
        for (int i = 0; i < balance; i++) {
            sb.append(')');
        }
        out.print(sb.toString());
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
 
        int nextInt() {
            return Integer.parseInt(next());
        }
    }
}