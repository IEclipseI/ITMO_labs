import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N28 {
    static void swap(List<Integer> ar,int i , int j) {
        int tmp = ar.get(i);
        ar.set(i, ar.get(j));
        ar.set(j, tmp);
    }
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader(new File("nextmultiperm.in")));
        PrintWriter out = new PrintWriter(new File("nextmultiperm.out"));
        int n = Integer.parseInt(in.readLine());
        if (n == 1) {
            out.print(0);
            out.close();
            return;
        }
        StringTokenizer strt = new StringTokenizer(in.readLine());
        List<Integer> ar2 = new ArrayList<Integer>();
        while (strt.hasMoreTokens()) {
            ar2.add(Integer.parseInt(strt.nextToken()));
        }
        for (int i = ar2.size() - 1; i > 0; i--) {
            if (ar2.get(i - 1) < ar2.get(i)) {
                for (int j = ar2.size() - 1; j > 0;j--) {
                    if  (ar2.get(j) > ar2.get(i - 1)) {
                        swap(ar2, i - 1, j);
                        break;
                    }
                }                   
                for (int j = 0; j < (ar2.size() - i) /2; j++) {
                    swap(ar2, i + j, ar2.size() - 1- j);
                }
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < ar2.size(); j++) {
                     sb.append(Integer.toString(ar2.get(j)) + " ");
                }
                sb.deleteCharAt(sb.length() - 1);
                out.print(sb.toString());
                break;
            }
            if (i == 1) {
                StringBuilder sb = new StringBuilder();
                for (int j = 0; j < n; j++) {
                     sb.append("0 ");
                }
                sb.deleteCharAt(sb.length() - 1);
                out.print(sb.toString());
            }
        }
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