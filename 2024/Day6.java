import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Day6 {

    static class Movement {
        int xAxis;
        int yAxis;
        char sign;

        public static final Movement[] directions = {
            new Movement(-1, 0, '^'),
            new Movement(0, 1, '>'),
            new Movement(1, 0, 'v'),
            new Movement(0, -1, '<')
        };

        public Movement(int x, int y, char sign){
            this.xAxis = x;
            this.yAxis = y;
            this.sign = sign;
        }
    }
    
    public static List<char[]> readFile(String filePath) {
        File file = new File(filePath);
        List<char[]> input = new ArrayList<>();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            while((line = reader.readLine()) != null) {
                input.add(line.toCharArray());
            }
            reader.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
        return input;
    }
    
    public static void main (String[] args) {
        int[] position = {0,0};
        List<char[]> data = readFile("/Users/gauravshah/Developer/Advent of Code/2024/input_06.txt");

        int n = data.size();
        char[][] arr = new char[n][];
        for(int x =0 ; x< n; x++){
            arr[x] = data.get(x);
        }
        int m = arr[0].length;

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(arr[i][j] != '#' && arr[i][j] != '.') {
                    position[0] = i;
                    position[1] = j;
                    break;
                }
            }
        }
        //System.out.println("initial starting pos : " + position[0] + ", " + position[1]);
        int dir=0;
        for(;dir<4;dir++){
            if(arr[position[0]][position[1]] == Movement.directions[dir].sign) {
                arr[position[0]][position[1]] = '.';
                break;
            }
        }
        //System.out.println("initial dir : " + dir);
        int steps = 0;
        while(position[0]<n && position[1]<m && position[0]>=0 && position[1]>=0){
            if(arr[position[0]][position[1]] == '.') {
                arr[position[0]][position[1]] = 'X';
                steps++;
            }
            int k = position[0]+Movement.directions[dir].xAxis;
            int l = position[1]+Movement.directions[dir].yAxis;
            while(k<n && k>=0 && l<m && l>=0) {
                if(arr[k][l] == '#') dir = (dir+1)%4;
                else break;
                k = position[0]+Movement.directions[dir].xAxis;
                l = position[1]+Movement.directions[dir].yAxis;
            }
            position[0]+=Movement.directions[dir].xAxis;
            position[1]+=Movement.directions[dir].yAxis;
        }

        // for(int i=0;i<n;i++){
        //     System.out.println(arr[i]);
        // }
        System.out.println("output of first part: " + steps);
    }
}
