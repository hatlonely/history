package hl;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class HelloWords
 */
@WebServlet("/HelloWords")
public class HelloWords extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final ArrayList<String> words = helloWords();
    private Random random = new Random();

    private static ArrayList<String> helloWords() {
        ArrayList<String> words = new ArrayList<String>();

        try {
            File file = new File("/Users/hatlonely/hatlonely/git_workspace/hellowords/data/one.txt");
            if (!file.isFile() || !file.exists()) {
                return words;
            }
            InputStreamReader inputStreamReader = new InputStreamReader(new FileInputStream(file),
                    "utf-8");
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            String line = null;
            while ((line = bufferedReader.readLine()) != null) {
                if (line.indexOf('\t') != -1) {
                    words.add(line.split("\t")[1]);
                }
            }
            bufferedReader.close();
        } catch (Exception e) {

        }

        return words;
    }

    /**
     * @see HttpServlet#HttpServlet()
     */
    public HelloWords() {
        super();
    }

    /**
     * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/htm; charset=utf-8");
        response.getWriter().println(words.get(random.nextInt(words.size())));
    }

    /**
     * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse
     *      response)
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/htm; charset=utf-8");
        response.getWriter().println(words.get(random.nextInt(words.size())));
    }

}
