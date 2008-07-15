//Pour avoir le mode debug de glib il faut d�finir la variable d'environnement G_DEBUG
//-> http://library.gnome.org/devel/glib/stable/glib-running.html

gst-launch-0.10 videotestsrc ! video/x-raw-rgb ! glimagesink

gst-launch-0.10 videotestsrc ! glgraphicmaker ! glimagesink

gst-launch-0.10 -v videotestsrc ! glgraphicmaker ! glimagesink

gst-launch-0.10 --gst-debug-level=3 videotestsrc ! glgraphicmaker ! glimagesink

videotestsrc num_buffers=200 ! video/x-raw-rgb, framerate = 25/1, width=320, height=240 !  tee name=teee teee. ! queue ! glimagesink teee. ! queue ! glimagesink teee. ! queue ! glimagesink

videotestsrc num_buffers=200 ! video/x-raw-yuv, format=(fourcc)I420, framerate = 25/1, width=320, height=240 !  tee name=t t. ! queue ! glimagesink t. ! queue ! glimagesink t. ! queue ! glimagesink

videotestsrc num_buffers=200 ! video/x-raw-yuv, format=(fourcc)YUY2, framerate = 25/1, width=320, height=240 !  tee name=t t. ! queue ! glimagesink t. ! queue ! glimagesink t. ! queue ! glimagesink

videotestsrc num_buffers=200 ! video/x-raw-yuv, format=(fourcc)YV12, framerate = 25/1, width=320, height=240 !  tee name=t t. ! queue ! glimagesink t. ! queue ! glimagesink t. ! queue ! glimagesink

videotestsrc num_buffers=200 ! video/x-raw-rgb, framerate = 25/1, width=320, height=240 !  tee name=teee teee. ! queue ! glgraphicmaker ! glimagesink teee. ! queue ! glgraphicmaker ! glimagesink teee. ! queue ! glgraphicmaker ! glimagesink




Id�e pour faire un pool de textures: (consid�rations pour une texture "rgb", "yuv" �tant une g�n�ralisation)

Dans un programme opengl normal, on appel une unique fois glGenTextures (couteux) puis on l'actualise � chaque fois 
avec glTexImage2D.
Donc dans ce cas la consommation de ressources est optimale.

Cependant dans le context de graph, le glbuffer, qui contient une texture, est sujet � passer de filtre en filtre.
Et donc � priori on ne s'est pas � l'avance ce qu'il va devenir. Ce qui implique que l'on est oblig� d'appeler
glGenTextures � chaque nouvelle frame. C'est ce qui est fait actuellement.

Un pool de textures permettrait donc de diminuer consid�rablemet le nombre d'appels � glGenTextures.
Cependant un pool de textures simple, c'est � dire avec un nombre fixe d'appels � glGenTextures n'est pas
r�alisable.
En effet, du fait qu'on ne s'est pas � l'avance ce que vont devenir les glbuffers, il est impossible de d�terminer
la taille minimale du pool.

Mais dans l'architechture de ce plugin opengl, on a la chance d'avoir un contexte commun � toute une branche 
de la pipeline, le GstGLDisplay. (A noter que le "contexte" commun � toute ces branches est la map)

De ce fait je propose la chose suivante:

Le pool est constitu� d'une Queue de GLuint.
Il y aura un pool par contexte GstGLDisplay.
Au d�part le pool est de taille 0. 
A chaque nouvelle frame, si le pool est de taille 0 alors le glbuffer cr�e fait appel � un glGenTextures. 
Lorsque le buffer est d�truit, il le signal au contexte GstGLDisplay qui lui va ajouter � la Queue le GLuint utilis�.
Lorsqu'une nouvelle frame arrive et que le pool n'est pas de taille 0, le glbuffer cr�e, pop la Queue et utilise le GLuint 
directement sans faire appel � glGenTextures.
A la fin du stream, plus aucune frame arrive et donc plus aucun glbuffer est cr�e.
Les glbuffer qui naviguaient dans la pipeline sont peu � peu d�truits, ce qui augmente peu � peu la taille de la Queue.
Si le stream est � nouveau jou�, on fait pareil que d�crit pr�c�demment.
Si la branche de la pipeline est totalement d�truite, le compteur de r�f�rence de son contexte GstGLDisplay atteint 0, 
le destructeur est appel� et on vide la Queue en tachant de faire un glDeleteTextures � pour chaque GLuint pop�.

Affin de g�r� le "yuv", il y aura non pas une Queue de GLuint mais une Queue de tripl� GLuint