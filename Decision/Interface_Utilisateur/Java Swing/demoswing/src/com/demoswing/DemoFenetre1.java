package com.demoswing;

import javax.swing.JFrame;

public class DemoFenetre1 {

	/**
	 * 
	 * @param args
	 */
	
	public static void main(String[] args) {
		
		// TODO 1. Instancier une JFrame
		JFrame maFenetre1 = new JFrame();
		
		// TODO 2. Modifier le titre de la fenetre
		maFenetre1.setTitle("Fenetre UI Decision");
		
		// TODO 3. Modifier la taille (400 * 300)
		maFenetre1.setSize(400, 300);
		
		// TODO 4. Taille non modifiable par l'utilisateur
		maFenetre1.setResizable(false);
		
		// TODO 5. Cliquer sur Croix pour fermer la fenetre
		maFenetre1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// TODO 6. Afficher la JFrame
		maFenetre1.setVisible(true);

	}

}
