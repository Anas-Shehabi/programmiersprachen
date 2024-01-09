/*************************************************
* ADS Praktikum 2.2
* Tree.cpp
* Erweiterung um Hilfsfunktionen gestattet.
*************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>
#include <iomanip>

using namespace std;

TreeNode* getTargetTwoRedFollowing(TreeNode* act)
{
	TreeNode* targetTwoRedFollowing = nullptr;

	// Achtung Zugriffverletzung vorbeugen
	if (act->getRight() != nullptr && act->getRight()->getRight() != nullptr &&
		act->getRight()->getRed() == true && act->getRight()->getRight()->getRed() == true)
	{
		targetTwoRedFollowing = act;
	}
	else if (act->getLeft() != nullptr && act->getLeft()->getLeft() != nullptr &&
		act->getLeft()->getRed() == true && act->getLeft()->getLeft()->getRed() == true)
	{
		targetTwoRedFollowing = act;
	}
	else if (act->getRight() != nullptr && act->getRight()->getLeft() != nullptr &&
		act->getRight()->getRed() == true && act->getRight()->getLeft()->getRed() == true)
	{
		targetTwoRedFollowing = act;
	}
	else if (act->getLeft() != nullptr && act->getLeft()->getRight() != nullptr &&
		act->getLeft()->getRed() == true && act->getLeft()->getRight()->getRed() == true)
	{
		targetTwoRedFollowing = act;
	}
	
	
	
	/*if (act->getLeft() != nullptr && 
		act->getRight() != nullptr && 
		act->getRight()->getRight() != nullptr &&  
		act->getLeft()->getLeft() != nullptr &&
		act->getRight()->getLeft()!= nullptr && 
		act->getLeft()->getRight() != nullptr &&
		
		(
			(act->getRight()->getRed() == true && act->getRight()->getRight()->getRed() == true)
			||
			(act->getLeft()->getRed() == true && act->getLeft()->getLeft()->getRed() == true)
			||
			(act->getRight()->getRed() == true && act->getRight()->getLeft()->getRed() == true)
			||
			(act->getLeft()->getRed() == true && act->getLeft()->getRight()->getRed() == true))
		)
	{
		targetTwoRedFollowing = act;

	}*/





	if (act->getLeft() != nullptr)
	{
		if (targetTwoRedFollowing == nullptr)
		{
			targetTwoRedFollowing = getTargetTwoRedFollowing(act->getLeft());
		}
	}

	if (act->getRight() != nullptr)
	{
		if (targetTwoRedFollowing == nullptr)
		{
			targetTwoRedFollowing = getTargetTwoRedFollowing(act->getRight());
		}
	}

	return targetTwoRedFollowing;
}

////////////////////////////////////
// Ihr Code hier:

bool Tree::balanceTree()
{
	bool blackFollowedBy2RedsRemaining = true;
	
	TreeNode* target; 
	

	while (blackFollowedBy2RedsRemaining)
	{
		target = getTargetTwoRedFollowing(anker);

		if (target == nullptr)
		{
			blackFollowedBy2RedsRemaining = false;
			break;
		}
		//Rotationsart wählen
		else
		{
			TreeNode* base = target;
			TreeNode* firstRed = nullptr;
			TreeNode* secondRed = nullptr;
			
			if (target->getRight() != nullptr && target->getRight()->getRight() != nullptr &&
				target->getRight()->getRed() == true && target->getRight()->getRight()->getRed() == true)
			{
				firstRed = target->getRight();
				secondRed = target->getRight()->getRight();

				//links
				rotateTreeLeft(firstRed, secondRed);

			}
			else if (target->getLeft() != nullptr && target->getLeft()->getLeft() != nullptr &&
				target->getLeft()->getRed() == true && target->getLeft()->getLeft()->getRed() == true)
			{
				firstRed = target->getLeft();
				secondRed = target->getLeft()->getLeft();
				// rechts
				rotateTreeRight(firstRed, secondRed);
			}
			else if (target->getLeft() != nullptr && target->getLeft()->getRight() != nullptr &&
				target->getLeft()->getRed() == true && target->getLeft()->getRight()->getRed() == true)
			{
				firstRed = target->getLeft();
				secondRed = target->getLeft()->getRight();
				// links rechts

				rotateTreeLeft(firstRed, secondRed);
				rotateTreeRight(secondRed, firstRed);

			}
			else if (target->getRight() != nullptr && target->getRight()->getLeft() != nullptr &&
				target->getRight()->getRed() == true && target->getRight()->getLeft()->getRed() == true)
			{
				firstRed = target->getRight();
				secondRed = target->getRight()->getLeft();
				
				// rechts links
				rotateTreeRight(firstRed, secondRed);
				rotateTreeLeft(secondRed, firstRed);
				

			}
			else
			{
				cout << "Target Nachfolgerermittlung fehlgeschlagen ... " << endl;
			}






			

		}



	}

	return true;
}

int Tree::height(TreeNode* node)
{
	if (node == nullptr)
		return 0;
	else
	{
		/* compute the height of each subtree */
		int lheight = height(node->getLeft());
		int rheight = height(node->getRight());

		/* use the larger one */
		if (lheight > rheight)
			return(lheight + 1);
		else return(rheight + 1);
	}
}

bool Tree::rotateTreeRight(TreeNode* firstRed, TreeNode* secondRed)
{
	TreeNode* parent = getParent(anker, firstRed);

	// einfache rechtsrotation
	if (parent->getLeft() == firstRed)
	{
		TreeNode* parentParent = getParent(anker, parent);
		if (parentParent == nullptr) // anker wird gedreht
		{
			anker = firstRed;
		}		
		else if (parentParent->getLeft() == parent)
		{
			parentParent->setLeft(firstRed);
		}
		else
		{
			parentParent->setRight(firstRed);
		}

		parent->setLeft(firstRed->getRight());
		firstRed->setRight(parent);

		parent->setRed(true);
		firstRed->setRed(false);


	}
	// rechtsrotation (lr-rotation)
	else if (parent->getRight() == firstRed)
	{
		parent->setRight(secondRed);
		firstRed->setLeft(secondRed->getRight());
		secondRed->setRight(firstRed);


	}
	   	  	

	return true;
}

bool Tree::rotateTreeLeft(TreeNode* firstRed, TreeNode* secondRed)
{
	TreeNode* parent = getParent(anker, firstRed);
	
	// einfache linksrotation
	if (parent->getRight() == firstRed)
	{
		TreeNode* parentParent = getParent(anker,parent);
		if (parentParent == nullptr)
		{
			anker = firstRed;
		}
		else if (parentParent->getLeft() == parent)
		{
			parentParent->setLeft(firstRed);
		}
		else
		{
			parentParent->setRight(firstRed);
		}


		
		parent->setRight(firstRed->getLeft());
		firstRed->setLeft(parent);

		parent->setRed(true);
		firstRed->setRed(false);

	}
	// linksrotation (lr-rotation)
	else if (parent->getLeft() == firstRed)
	{
		parent->setLeft(secondRed);
		firstRed->setRight(secondRed->getLeft());
		secondRed->setLeft(firstRed);


	}

	

	return true;
}

///////////////////////////

TreeNode* Tree::getParent(TreeNode* act, TreeNode* child)
{
	TreeNode* parent = nullptr;

	if (act->getLeft() == child || act->getRight() == child)
	{
		parent = act;

	}

	if (act->getLeft() != nullptr)
	{
		if (parent == nullptr)
		{
			parent = getParent(act->getLeft(), child);
		}
	}

	if (act->getRight() != nullptr)
	{
		if (parent == nullptr)
		{
			parent = getParent(act->getRight(), child);
		}
	}

	return parent;

}

bool Tree::searchTree(TreeNode* act, string Name)
{
	bool success = false;
	bool successLeft = false;
	bool successRigth = false;

	if (act->getName() == Name)
	{
		cout << "NodeId: " << act->getNodeID() << ", Name: " << act->getName()
			<< ", Alter: " << act->getAlter() << ", Einkommen:" << act->getEinkommen()
			<< ", PLZ: " << act->getPLZ() << ", PosID: " << act->getNodePosID() << endl;
		success = true;
	}

	if (act->getLeft() != nullptr)
	{
		successLeft = searchTree(act->getLeft(), Name);
	}

	if (act->getRight() != nullptr)
	{
		successRigth = searchTree(act->getRight(), Name);
	}

	return success || successLeft || successRigth;
}

void Tree::preOrder(TreeNode * act)
{
	cout << left << setw(3) << act->getNodeID() << "|" << right << setw(13) << act->getName() << "|" << right << setw(7) << act->getAlter() << "|"
		<< right << setw(11) << act->getEinkommen() << "|" << right << setw(11) << act->getPLZ() << "|" << act->getNodePosID() << endl;

	if (act->getLeft() != nullptr)
	{
		preOrder(act->getLeft());
	}
	if (act->getRight() != nullptr)
	{
		preOrder(act->getRight());
	}

}

void Tree::printExactLevel(TreeNode * act, int printLevel, int currentLevel)
{
	if (printLevel == currentLevel)
	{
		cout << left << setw(3) << act->getNodeID() << "|" << right << setw(13) << act->getName() << "|" << right << setw(7) << act->getAlter() << "|"
			<< right << setw(11) << act->getEinkommen() << "|" << right << setw(11) << act->getPLZ() << "|" << right << setw(7)<< act->getNodePosID() << "|" 
			<< right << setw(2) << act->getRed() << endl;
	}

	++currentLevel;

	if (act->getLeft() != nullptr)
	{
		printExactLevel(act->getLeft(), printLevel, currentLevel);
	}
	if (act->getRight() != nullptr)
	{
		printExactLevel(act->getRight(), printLevel, currentLevel);
	}

}

void Tree::printLevelOrder()
{
	cout << "ID" << " | " << "Name\t" << " | " << "Alter" << " | "
		<< "Einkommen" << " | " << "PLZ\t" << " | " << "Pos\t" << " | " << "Red\t" << endl;

	cout << "---+-------------+-------+-----------+-----------+-------+-------" << endl;

	int tiefe = height(anker);

	for (int i = 0; i < tiefe; i++)
	{
		printExactLevel(anker, i, 0);
	}

}

Tree::Tree()
{
}

void Tree::addNode(string Name, int Alter, double Einkommen, int PLZ)
{
	TreeNode* neuerEintrag = new TreeNode(Alter + PLZ + Einkommen, NodeIDCounter++, Name, Alter, Einkommen, PLZ);

	// Neuer Eintrag ist rot rs
	neuerEintrag->setRed(true);


	if (anker == nullptr)
	{
		anker = neuerEintrag;
		anker->setRed(false);
	}
	else
	{
		TreeNode* runner = anker;

		bool lastDirectionLeft;

		//Positionsermittlung
		while (true)
		{
			// beim Durchgehen schwarz mit 2 roten Nachfolgern umfärben
			if (runner->getLeft() != nullptr &&
				runner->getRight() != nullptr &&
				runner->getRed() == false &&
				runner->getLeft()->getRed() == true &&
				runner->getRight()->getRed() == true )
			{
				runner->setRed(true);
				runner->getLeft()->setRed(false);
				runner->getRight()->setRed(false);				
				
				if (getTargetTwoRedFollowing(anker) != nullptr)
				{
					balanceTree();
				}
				
				runner = anker;
				continue;

			
			}

			

			

			if (neuerEintrag->getNodePosID() < runner->getNodePosID())
			{
				if (runner->getLeft() != nullptr)
				{
					runner = runner->getLeft();
				}
				else
				{
					lastDirectionLeft = true;
					break;
				}

			}
			else if (neuerEintrag->getNodePosID() > runner->getNodePosID())
			{
				if (runner->getRight() != nullptr)
				{
					runner = runner->getRight();
				}
				else
				{
					lastDirectionLeft = false;
					break;
				}

			}


		}



		//Einfügeoperation
		if (lastDirectionLeft)
		{
			runner->setLeft(neuerEintrag);
			
		}
		else
		{
			runner->setRight(neuerEintrag);
		}

		anker->setRed(false);

		// Balance muss nach jedem Einfuegen getriggert werden
		balanceTree();



	}



}

void Tree::deleteNode(int NodePosID)
{
	TreeNode* target = nullptr;
	TreeNode* parentTarget = nullptr;
	bool targetIsLeft = false;

	bool targetFound = false;


	if (anker != nullptr)
	{
		target = anker;

		while (true)
		{
			if (target->getNodePosID() == NodePosID)
			{
				targetFound = true;
				break;
			}

			if (target->getNodePosID() > NodePosID)
			{
				if (target->getLeft() != nullptr)
				{
					parentTarget = target;
					targetIsLeft = true;
					target = target->getLeft();
				}
				else
				{
					break;
				}
			}

			if (target->getNodePosID() < NodePosID)
			{
				if (target->getRight() != nullptr)
				{
					parentTarget = target;
					targetIsLeft = false;
					target = target->getRight();
				}
				else
				{
					break;
				}
			}
		}
	}

	if (targetFound == true)
	{
		//Fallunterscheidung
		if (target->getLeft() == nullptr && target->getRight() == nullptr)
		{
			// anker ohne Äste wird gelöscht
			if (target == anker)
			{
				anker = nullptr;
			}

			delete target;

			// Ziel hatte Parent
			if (parentTarget != nullptr)
			{
				// Linker Ast schaut nun auf nullptr
				if (targetIsLeft)
				{
					parentTarget->setLeft(nullptr);
				}
				// Rechter Ast schaut nun auf nullptr
				else
				{
					parentTarget->setRight(nullptr);
				}
			}
		}
		else if (target->getLeft() != nullptr && target->getRight() == nullptr)
		{
			if (parentTarget != nullptr)
			{
				// Target mit einem Nachfolger links wird gelöscht (Parent hat Target links)
				if (targetIsLeft)
				{
					parentTarget->setLeft(target->getLeft());
				}
				// Target mit einem Nachfolger links wird gelöscht (Parent hat Target rechts)
				else
				{
					parentTarget->setRight(target->getLeft());
				}
			}
			// Anker wird gelöscht mit linkem Nachfolger
			else
			{
				anker = target->getLeft();
			}

			delete target;
		}
		else if (target->getLeft() == nullptr && target->getRight() != nullptr)
		{
			//vgl vorherigen Fall nur umgekehrt

			if (parentTarget != nullptr)
			{
				if (targetIsLeft)
				{
					parentTarget->setLeft(target->getRight());
				}
				else
				{
					parentTarget->setRight(target->getRight());
				}
			}
			else
			{
				anker = target->getRight();
			}

			delete target;
		}
		else if (target->getLeft() != nullptr && target->getRight() != nullptr)
		{
			TreeNode* minimum = target->getRight();
			TreeNode* preMinimum = target;

			bool setNptrPreMin = false;

			while (true)
			{
				if (minimum->getLeft() != nullptr)
				{
					preMinimum = minimum;
					minimum = minimum->getLeft();
					setNptrPreMin = true; // Wenn Minimum tiefer im Baum liegt als direkt nach Target 
										  // müssen wir den Vorgänger von Minimum nullptr setzen
										  // Denn der Vorgänger verliert seinen Nachfolger Min
				}
				else
				{
					break;
				}

			}


			if (setNptrPreMin)
			{
				// Minimum kann keinen Partner haben...
				if (minimum->getRight() == nullptr)
				{
					preMinimum->setLeft(nullptr);
				}
				// oder nur einen rechten ...
				else
				{
					preMinimum->setLeft(minimum->getRight());
				}
			}


			if (parentTarget != nullptr)
			{
				//Parent des Target mit Minimum verknüpfen

				if (targetIsLeft)
				{
					parentTarget->setLeft(minimum);
				}
				else
				{
					parentTarget->setRight(minimum);
				}



				// Hier verbinden wir Minimum mit den Nachfolgern vom zu löschenden Target
				// Dies geschieht nur wenn der Nachfolger von Target nicht Minimum ist
				// Sonst würde Minimum auf sich selbst zeigen -> Datenverlust
				if (target->getLeft() != minimum)
				{
					minimum->setLeft(target->getLeft());
				}

				if (target->getRight() != minimum)
				{
					minimum->setRight(target->getRight());
				}

				delete target;




			}
			else // Anker wird gelöscht
			{
				if (target->getLeft() != minimum)
				{
					minimum->setLeft(target->getLeft());
				}

				if (target->getRight() != minimum)
				{
					minimum->setRight(target->getRight());
				}

				delete target;


				// Weil anker gelöscht wird setzen wir ihn neu
				anker = minimum;

			}





		}

		cout << "+ Datensatz wurde geloescht." << endl;

	}
	else
	{
		cout << "+ Datensatz nicht gefunden" << endl;
	}


}

bool Tree::searchNode(string Name)
{
	if (anker != nullptr)
	{
		return searchTree(anker, Name);
	}

	return false;

}

void Tree::printAll()
{
	cout << "ID" << " | " << "Name\t" << " | " << "Alter" << " | "
		<< "Einkommen" << " | " << "PLZ\t" << " | " << "Pos\t" << endl;

	cout << "---+-------------+-------+-----------+-----------+-------" << endl;

	if (anker != nullptr)
	{
		preOrder(anker);
	}
}

//
////////////////////////////////////