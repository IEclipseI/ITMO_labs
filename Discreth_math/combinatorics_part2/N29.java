import java.io.*;
import java.util.*;
import java.lang.Math;
import java.util.concurrent.ArrayBlockingQueue;
 
public class N29 {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(new File("nextpartition.in"));
        PrintWriter out = new PrintWriter(new File("nextpartition.out"));
        List<String> answer = new ArrayList<String>();
        StringBuilder sb = new StringBuilder();
        List<Integer> now = new ArrayList<Integer>();
        StringTokenizer string = new StringTokenizer(in.next(), "+=");
        int n = Integer.parseInt(string.nextToken());
        while (string.hasMoreTokens()) {
            now.add(Integer.parseInt(string.nextToken()));
        }
        if (now.get(0) == n) {
            out.print("No solution");
        } else {
            now.set(now.size() - 1, now.get(now.size() - 1) - 1);
            now.set(now.size() - 2, now.get(now.size() - 2) + 1);
            if (now.get(now.size() - 1) < now.get(now.size() - 2)) {
                now.set(now.size() - 2, now.get(now.size() - 2) + now.get(now.size() - 1));
                now.remove(now.size() - 1);
            } else {
                while (now.get(now.size() - 1)/2 >= now.get(now.size() - 2)) {
                    int cur = now.get(now.size() - 1);
                    now.remove(now.size() - 1);
                    now.add(now.get(now.size() - 1));
                    now.add(cur - now.get(now.size() - 1));
                }
            }
            sb = new StringBuilder();
            for (int numb : now) {
                sb.append(numb + "+");
            }
            sb.deleteCharAt(sb.length() - 1);
            out.print(n + "=");
            answer.add(sb.toString());
            for (String str: answer) {
                //for(int i = 0; i <l; i++) {
                  //  char ch = str.charAt(i);
                    out.print(str);
                //}
                out.println();
                //numb++;
            }
        }
        //System.out.println(answer.size());        
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