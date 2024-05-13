import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.ScrollPaneConstants;

import java.awt.Color;
import java.awt.event.WindowEvent;

public class MainWindow extends JFrame {
    private static final long serialVersionUID = 1L;

    private JTextArea textArea;
    private JScrollPane scrollPane;

    private static Client client = null;

    public static void main(String[] args) {
        MainWindow window = new MainWindow();

        try {
            client = new Client(Client.DEFAULT_HOST, Client.DEFAULT_PORT);
        } catch (Exception e) {
            window.writeLine("Client: Couldn't connect to " + Client.DEFAULT_HOST + ":" + Client.DEFAULT_PORT);
            client = null;
        }

        if (client != null) {
            window.writeLine("Client connected to " + Client.DEFAULT_HOST + ":" + Client.DEFAULT_PORT);
        }
    }

    public MainWindow() {
        super("INF 224");
        setSize(500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        initUI();

        setVisible(true);
    }

    private void initUI() {

        textArea = new JTextArea();

        textArea.setWrapStyleWord(true);
        textArea.setLineWrap(true);
        textArea.setEditable(false);

        scrollPane = new JScrollPane(textArea, ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
                ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        add(scrollPane, "Center");

        JTextField playField = new JTextField();
        JTextField displayField = new JTextField();

        Action actionExit = new AbstractAction("Exit") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent e) {
                dispatchEvent(new WindowEvent(MainWindow.this, WindowEvent.WINDOW_CLOSING));
            }
        };
        Action actionDisplay = new AbstractAction("Display info") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent e) {
                String request = "display " + displayField.getText();
                displayField.setText("");
                String response = sendRequest(request);
                writeLine("Request: " + request);
                writeLine("Response: " + response);
            }
        };
        Action actionPlay = new AbstractAction("Play") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent e) {
                String request = "play " + playField.getText();
                playField.setText("");
                String response = sendRequest(request);
                writeLine("Request: " + request);
                writeLine("Response: " + response);
            }
        };
        Action actionList = new AbstractAction("List") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent e) {
                String request = "list";
                String response = sendRequest(request);
                writeLine("Request: " + request);
                writeLine("Response: " + response);
            }
        };

        Action actionClear = new AbstractAction("Clear") {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent e) {
                textArea.setText("");
            }
        };

        // Add the button panel
        // Two buttons with a text field and one exit button
        JPanel panel = new JPanel();
        JPanel panelDisplay = new JPanel();
        JPanel panelPlay = new JPanel();
        // text field is above the button
        panelDisplay.setLayout(new java.awt.GridLayout(2, 1));
        panelPlay.setLayout(new java.awt.GridLayout(2, 1));

        panelDisplay.add(displayField);
        panelPlay.add(playField);

        JButton displayButton = new JButton(actionDisplay);
        displayButton.setForeground(Color.RED); // Color the button text
        panelDisplay.add(displayButton);

        JButton playButton = new JButton(actionPlay);
        playButton.setForeground(Color.BLUE); // Color the button text
        panelPlay.add(playButton);

        panel.add(panelDisplay);
        panel.add(panelPlay);

        JButton listButton = new JButton(actionList);
        listButton.setForeground(Color.GREEN); // Color the button text
        panel.add(listButton);

        add(panel, "South");

        // Add the menu bar
        JMenuBar menuBar;
        JMenu menuFile;

        setJMenuBar(menuBar = new JMenuBar());
        menuBar.add(menuFile = new JMenu("File"));

        menuFile.add(actionClear);
        menuFile.add(actionExit);

        // Add toolbar
        JToolBar toolBar = new JToolBar();
        // toolBar.add(panelDisplay);
        // toolBar.add(panelPlay);
        toolBar.add(actionClear);
        toolBar.add(actionExit);

        add(toolBar, "North");
    }

    public void writeLine(String line) {
        textArea.append(line + "\n");
        // Auto scroll to bottom
        textArea.setCaretPosition(textArea.getDocument().getLength());
    }

    private static String sendRequest(String request) {
        if (client == null) {
            return "Client not connected";
        }
        String response = client.send(request);
        return response;
    }
}
