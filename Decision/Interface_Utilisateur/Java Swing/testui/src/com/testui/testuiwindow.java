
/**
 * @author Lulu
 *
 */

package com.testui;

import javax.swing.JFrame;

import java.awt.color.*;

import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.border.Border;
import javax.swing.BorderFactory;


public class testuiwindow {

	public static void main(String[] args) {
		
		JFrame maFenetre1 = new JFrame(); 								// TODO 1. Instancier une JFrame		
		maFenetre1.setTitle("Fenetre Test UI Decision"); 					// TODO 2. Modifier le titre de la fenetre		
		maFenetre1.setSize(400, 300); 									// TODO 3. Modifier la taille (400 * 300)
		maFenetre1.setResizable(false); 								// TODO 4. Taille non modifiable par l'utilisateur
		maFenetre1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 		// TODO 5. Cliquer sur Croix pour fermer la fenetre
		
		
		
		 JLabel text = new JLabel("text");
		   // text.border = BorderFactory.createLineBorder();
		   // text.setBorder(border);
		   // text.setPreferredSize(new Dimension(150, 100));
		    
		    text.setText("Bonjour je suis un texte");
		    text.setHorizontalAlignment(JLabel.CENTER);
		    text.setVerticalAlignment(JLabel.CENTER);
		
		maFenetre1.add(text);
		maFenetre1.setVisible(true); 
	}
	
	
}