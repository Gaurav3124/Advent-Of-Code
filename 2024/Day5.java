// import java.io.BufferedReader;
// import java.nio.charset.Charset;
// import java.nio.file.Files;
// import java.nio.file.Path;
// import java.nio.file.Paths;
// import java.util.ArrayList;
// import java.util.HashMap;

// public class Day5 {
//     public static void main (String[] args) throws Exception {
//         Charset charset = Charset.forName("US-ASCII");
    
//         try {
//             Path file = Paths.get("/Users/gauravshah/Developer/Advent of Code/2024/input_05.txt");
//             BufferedReader reader = Files.newBufferedReader(file, charset);
//             String line;
//             ArrayList<ArrayList<Integer>> arrays = new ArrayList<>();
//             HashMap<Integer, Integer> mp = new HashMap<>();
//             Boolean isPage = true;
//             while((line = reader.readLine())!= null) {
//                 if(line.isBlank()) {
//                     isPage = false;
//                     continue;
//                 }
                
//                 if(isPage) {
//                     String regex = "\\|";
//                     String[] split = line.split(regex);
//                     mp.put(Integer.parseInt(split[0]),Integer.parseInt(split[1]));
//                 }
//                 else {
//                     String regex = ",";
//                     String[] split = line.split(regex);
//                     ArrayList<Integer> arr = new ArrayList<>();
//                     int n = split.length;
//                     for (int i=0;i <n; i++){
//                         Integer x = Integer.parseInt(split[i]);
//                         arr.add(x);
//                     }
//                     arrays.add(arr);
//                 }
//             }

//             var it = mp.entrySet().iterator();
//             while(it.hasNext()) System.out.println(it.next().getKey() + " " + it.next().getValue());
//             System.out.println();
            


//             reader.close();
//         } catch (Exception e) {
//             System.out.println("error occured");
//             throw e;
//         }
//     }
// }

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;



public class Day5 {
    public class FileIO {
        public static List<String> read(String filename) {
            Scanner file;
            try {
                file = new Scanner(new File(filename));
                List<String> out = new ArrayList<>();
                while (file.hasNextLine()) { out.add(file.nextLine()); }
                file.close();
                return out;
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
            return new ArrayList<>();
        }   
    }
    public static void main(String[] args) {
        List<String> input = FileIO.read("/Users/gauravshah/Developer/Advent of Code/2024/input_05.txt");

        Map<Integer, Page> rules = new HashMap<>();
        while(!input.get(0).isBlank()) {
            // Read in rules of which pages must go before (pre) and after (post) this Page
            int[] nums = Arrays.stream(input.get(0).split("\\|"))
                               .mapToInt(str -> Integer.parseInt(str))
                               .toArray();
            if (!rules.containsKey(nums[0]))     { rules.put(nums[0], new Page(nums[0])); }
            if (!rules.containsKey(nums[1])) { rules.put(nums[1], new Page(nums[1])); }
            
            rules.get(nums[0]).post.add(nums[1]);
            rules.get(nums[1]).pre.add(nums[0]);

            input.remove(0);
        }

        // Remove empty line
        input.remove(0);

        int sum = 0, sorted_sum = 0;
        for (String s : input) {
            // Get instructions
            int[] pages = Arrays.stream(s.split(",")).mapToInt(str -> Integer.parseInt(str)).toArray();
            boolean ordered = true;

            // Verify no pages are in the wrong place
            for (int p = 0; p < pages.length; p++) {
                // Check for pages defined to follow after appearing before this page
                for (int pre = 0; pre < p; pre++) {
                    if (rules.get(pages[p]).post.contains(pages[pre])) {
                        ordered = false;
                    }
                }
                // Check for pages defined to appear before following after this page
                for (int post = p + 1; post < pages.length; post++) {
                    if (rules.get(pages[p]).pre.contains(pages[post])) {
                        ordered = false;
                    }
                }
            }

            if (ordered) {
                sum += pages[pages.length/2];
            } else {
                // Sort the Pages, find the middle
                Page[] sort = Arrays.stream(pages).mapToObj(p -> rules.get(p)).toArray(Page[]::new);
                Arrays.sort(sort);
                sorted_sum += sort[sort.length/2].page;
            }
        }

        System.out.println("Day 05:");
        System.out.printf("Part 1: %d\n", sum);
        System.out.printf("Part 2: %d\n", sorted_sum);
    }

    static class Page implements Comparable<Page> {
        int page;
        List<Integer> pre = new ArrayList<>(), post = new ArrayList<>();
        
        public Page(int page) {
            this.page = page;
        }

        @Override
        public int compareTo(Day5.Page o) {
            if (this.pre.contains(o.page)) {
                return 1;
            } else {
                return -1;
            }
        }
    }
}