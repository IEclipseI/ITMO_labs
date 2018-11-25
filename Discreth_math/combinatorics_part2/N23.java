import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N23 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextvector.in"));
        PrintWriter out = new PrintWriter(new File("nextvector.out"));
        String vector = in.next();
        char[] vect1 = vector.toCharArray();
        char[] vect2 = vector.toCharArray();
        int mark = 0;


        while (true) {
            if (vect1.length - 1 - mark < 0) {
                out.println('-');
                break;
            }
            if (vect1[vect1.length - 1 - mark] == '0') {
                vect1[vect1.length - 1 - mark] = '1';
            } else {
                vect1[vect1.length - 1 - mark] = '0';
                out.println(new String(vect1));
                break;
            }
            mark++;
        } 
        mark = 0;
        while (true) {
            if (vect2.length - 1 - mark < 0) {
                out.print('-');
                break;
            }
            if (vect2[vect2.length - 1 - mark] == '1') {
                vect2[vect2.length - 1 - mark] = '0';
            } else {
                vect2[vect1.length - 1 - mark] = '1';
                out.print(new String(vect2));
                break;
            }
            mark++;
        }

                              
        out.println();        
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