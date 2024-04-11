��/ / * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 
 / / 
 
 / /   C o p y r i g h t   ( c )   M i c r o s o f t .   A l l   r i g h t s   r e s e r v e d . 
 
 / /   T h i s   c o d e   i s   l i c e n s e d   u n d e r   t h e   M I T   L i c e n s e   ( M I T ) . 
 
 / /   T H E   S O F T W A R E   I S   P R O V I D E D    A S   I S  ,   W I T H O U T   W A R R A N T Y   O F   A N Y   K I N D ,   E X P R E S S   O R   I M P L I E D ,   
 
 / /   I N C L U D I N G   B U T   N O T   L I M I T E D   T O   T H E   W A R R A N T I E S   O F   M E R C H A N T A B I L I T Y ,   
 
 / /   F I T N E S S   F O R   A   P A R T I C U L A R   P U R P O S E   A N D   N O N I N F R I N G E M E N T .   
 
 / /   I N   N O   E V E N T   S H A L L   T H E   A U T H O R S   O R   C O P Y R I G H T   H O L D E R S   B E   L I A B L E   F O R   A N Y   C L A I M ,   
 
 / /   D A M A G E S   O R   O T H E R   L I A B I L I T Y ,   W H E T H E R   I N   A N   A C T I O N   O F   C O N T R A C T ,   
 
 / /   T O R T   O R   O T H E R W I S E ,   A R I S I N G   F R O M ,   O U T   O F   O R   I N   C O N N E C T I O N   W I T H   
 
 / /   T H E   S O F T W A R E   O R   T H E   U S E   O R   O T H E R   D E A L I N G S   I N   T H E   S O F T W A R E . 
 
 / / 
 
 / / * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 
 
 
 / /   m a i n . c p p   :   D e f i n e s   t h e   e n t r y   p o i n t   f o r   t h e   a p p l i c a t i o n . 
 
 
 
 # i n c l u d e   " s t d a f x . h " 
 
 # i n c l u d e   " m a i n . h " 
 
 # i n c l u d e   " W i n C o m p . h " 
 
 
 
 u s i n g   n a m e s p a c e   w i n r t ; 
 
 u s i n g   n a m e s p a c e   W i n d o w s : : U I ; 
 
 u s i n g   n a m e s p a c e   W i n d o w s : : U I : : C o m p o s i t i o n ; 
 
 u s i n g   n a m e s p a c e   W i n d o w s : : U I : : C o m p o s i t i o n : : D e s k t o p ; 
 
 u s i n g   n a m e s p a c e   W i n d o w s : : U I : : I n p u t ; 
 
 
 
 
 
 # d e f i n e   M A X _ L O A D S T R I N G   1 0 0 
 
 # d e f i n e   C D S S H A R E D H A N D L E   0 x 1 2 3 9 8 7 
 
 # d e f i n e   C D S P O I N T E R I N F O   0 x 7 8 9 1 2 3 
 
 
 
 / /   G l o b a l   V a r i a b l e s : 
 
 H I N S T A N C E 	 h I n s t ;                                                               / /   c u r r e n t   i n s t a n c e 
 
 H A N D L E   r e c e i v e d H a n d l e ; 
 
 H A N D L E   p a r e n t P r o c c e s s ; 
 
 s t d : : w s t r i n g 	 	 s z T i t l e ;                           / /   T h e   t i t l e   b a r   t e x t 
 
 s t d : : w s t r i n g 	 	 s z W i n d o w C l a s s ;               / /   t h e   m a i n   w i n d o w   c l a s s   n a m e 
 
 H W N D 	 	 m _ c h i l d H W n d ; 
 
 W i n C o m p * 	 m _ w i n C o m p ; 
 
 
 
 H W N D   s e c o n d a r y H w n d ; 
 
 
 
 / /   F o r w a r d   d e c l a r a t i o n s   o f   f u n c t i o n s   i n c l u d e d   i n   t h i s   c o d e   m o d u l e : 
 
 A T O M                                 M y R e g i s t e r C l a s s ( H I N S T A N C E   h I n s t a n c e ) ; 
 
 B O O L                                 I n i t I n s t a n c e ( H I N S T A N C E ,   i n t ) ; 
 
 L R E S U L T   C A L L B A C K         W n d P r o c ( H W N D ,   U I N T ,   W P A R A M ,   L P A R A M ) ; 
 
 I N T _ P T R   C A L L B A C K         A b o u t ( H W N D ,   U I N T ,   W P A R A M ,   L P A R A M ) ; 
 
 
 
 b o o l   i s S e c o n d a r y   =   f a l s e ; 
 
 v o l a t i l e   b o o l   h a n d l e R e c e i v e d   =   f a l s e ; 
 
 
 
 i n t   A P I E N T R Y   w W i n M a i n ( _ I n _   H I N S T A N C E   h I n s t a n c e , 
 
                                           _ I n _ o p t _   H I N S T A N C E   h P r e v I n s t a n c e , 
 
                                           _ I n _   L P W S T R         l p C m d L i n e , 
 
                                           _ I n _   i n t               n C m d S h o w ) 
 
 { 
 
         i s S e c o n d a r y   =   w c s c m p ( l p C m d L i n e ,   L " S e c o n d a r y P r o c e s s " )   = =   0 ; 
 
 
 
         U N R E F E R E N C E D _ P A R A M E T E R ( h P r e v I n s t a n c e ) ; 
 
         U N R E F E R E N C E D _ P A R A M E T E R ( l p C m d L i n e ) ; 
 
 
 
         w i n r t : : i n i t _ a p a r t m e n t ( w i n r t : : a p a r t m e n t _ t y p e : : s i n g l e _ t h r e a d e d ) ; 
 
 
 
         / /   I n i t i a l i z e   g l o b a l   s t r i n g s 
 
         / / L o a d S t r i n g W ( h I n s t a n c e ,   I D S _ A P P _ T I T L E ,   s z T i t l e ,   M A X _ L O A D S T R I N G ) ; 
 
         / / L o a d S t r i n g W ( h I n s t a n c e ,   I D C _ V I R T U A L S U R F A C E S ,   s z W i n d o w C l a s s ,   M A X _ L O A D S T R I N G ) ; 
 
         s z T i t l e   =   i s S e c o n d a r y   ?   L " V i r t u a l S u r f a c e s . S e c o n d a r y "   :   L " V i r t u a l S u r f a c e s . P r i m a r y " ; 
 
         s z W i n d o w C l a s s   =   i s S e c o n d a r y   ?   L " C o m p o s i t i o n T i l e s . S e c o n d a r y "   :   L " C o m p o s i t i o n T i l e s . P r i m a r y " ; 
 
         M y R e g i s t e r C l a s s ( h I n s t a n c e ) ; 
 
         / /   P e r f o r m   a p p l i c a t i o n   i n i t i a l i z a t i o n : 
 
         i f   ( ! I n i t I n s t a n c e   ( h I n s t a n c e ,   n C m d S h o w ) ) 
 
         { 
 
                 r e t u r n   F A L S E ; 
 
         } 
 
 
 
         H A C C E L   h A c c e l T a b l e   =   L o a d A c c e l e r a t o r s ( h I n s t a n c e ,   M A K E I N T R E S O U R C E ( I D C _ V I R T U A L S U R F A C E S ) ) ; 
 
 	 
 
         M S G   m s g ; 
 
 
 
         / /   M a i n   m e s s a g e   l o o p : 
 
         w h i l e   ( G e t M e s s a g e ( & m s g ,   n u l l p t r ,   0 ,   0 ) ) 
 
         { 
 
                 i f   ( ! T r a n s l a t e A c c e l e r a t o r ( m s g . h w n d ,   h A c c e l T a b l e ,   & m s g ) ) 
 
                 { 
 
                         T r a n s l a t e M e s s a g e ( & m s g ) ; 
 
                         D i s p a t c h M e s s a g e ( & m s g ) ; 
 
                 } 
 
                 i f   ( h a n d l e R e c e i v e d ) 
 
                 { 
 
                         h a n d l e R e c e i v e d   =   f a l s e ; 
 
 
 
                         m _ w i n C o m p - > P r e p a r e V i s u a l s ( r e c e i v e d H a n d l e ) ; 
 
                         m _ w i n C o m p - > U p d a t e V i e w P o r t ( t r u e ) ; 
 
                         m _ w i n C o m p - > C o n f i g u r e I n t e r a c t i o n ( ) ; 
 
                 } 
 
         } 
 
         r e t u r n   ( i n t )   m s g . w P a r a m ; 
 
 } 
 
 
 
 
 
 / / 
 
 / /     F U N C T I O N :   M y R e g i s t e r C l a s s ( ) 
 
 / / 
 
 / /     P U R P O S E :   R e g i s t e r s   t h e   w i n d o w   c l a s s . 
 
 / / 
 
 A T O M   M y R e g i s t e r C l a s s ( H I N S T A N C E   h I n s t a n c e ) 
 
 { 
 
         W N D C L A S S E X W   w c e x ; 
 
 
 
         w c e x . c b S i z e   =   s i z e o f ( W N D C L A S S E X ) ; 
 
 
 
         w c e x . s t y l e                     =   C S _ H R E D R A W   |   C S _ V R E D R A W ; 
 
         w c e x . l p f n W n d P r o c         =   W n d P r o c ; 
 
         w c e x . c b C l s E x t r a           =   0 ; 
 
         w c e x . c b W n d E x t r a           =   0 ; 
 
         w c e x . h I n s t a n c e             =   h I n s t a n c e ; 
 
         w c e x . h I c o n                     =   L o a d I c o n ( h I n s t a n c e ,   M A K E I N T R E S O U R C E ( I D I _ V I R T U A L S U R F A C E S ) ) ; 
 
         w c e x . h C u r s o r                 =   L o a d C u r s o r ( n u l l p t r ,   I D C _ A R R O W ) ; 
 
         w c e x . h b r B a c k g r o u n d     =   ( H B R U S H ) ( C O L O R _ W I N D O W + 1 ) ; 
 
         w c e x . l p s z M e n u N a m e       =   M A K E I N T R E S O U R C E W ( I D C _ V I R T U A L S U R F A C E S ) ; 
 
         w c e x . l p s z C l a s s N a m e     =   s z W i n d o w C l a s s . c _ s t r ( ) ; 
 
         w c e x . h I c o n S m                 =   L o a d I c o n ( w c e x . h I n s t a n c e ,   M A K E I N T R E S O U R C E ( I D I _ S M A L L ) ) ; 
 
 
 
         r e t u r n   R e g i s t e r C l a s s E x W ( & w c e x ) ; 
 
 } 
 
 
 
 / / 
 
 / /       F U N C T I O N :   I n i t I n s t a n c e ( H I N S T A N C E ,   i n t ) 
 
 / / 
 
 / /       P U R P O S E :   S a v e s   i n s t a n c e   h a n d l e   a n d   c r e a t e s   m a i n   w i n d o w 
 
 / / 
 
 / /       C O M M E N T S : 
 
 / / 
 
 / /                 I n   t h i s   f u n c t i o n ,   w e   s a v e   t h e   i n s t a n c e   h a n d l e   i n   a   g l o b a l   v a r i a b l e   a n d 
 
 / /                 c r e a t e   a n d   d i s p l a y   t h e   m a i n   p r o g r a m   w i n d o w . 
 
 / / 
 
 B O O L   I n i t I n s t a n c e ( H I N S T A N C E   h I n s t a n c e ,   i n t   n C m d S h o w ) 
 
 { 
 
       h I n s t   =   h I n s t a n c e ;   / /   S t o r e   i n s t a n c e   h a n d l e   i n   o u r   g l o b a l   v a r i a b l e 
 
 
 
       H W N D   h W n d P a r e n t   =   C r e a t e W i n d o w W ( s z W i n d o w C l a s s . c _ s t r ( ) ,   s z T i t l e . c _ s t r ( ) ,   W S _ O V E R L A P P E D W I N D O W , 
 
             C W _ U S E D E F A U L T ,   0 ,   C W _ U S E D E F A U L T ,   0 ,   n u l l p t r ,   n u l l p t r ,   h I n s t a n c e ,   n u l l p t r ) ; 
 
 
 
       i f   ( ! h W n d P a r e n t ) 
 
       { 
 
             r e t u r n   F A L S E ; 
 
       } 
 
 
 
       / / C r e a t e   t h e   c h i l d   H W N D   w i t h   t h e   s a m e   s i z e   a s   t h e   p a r e n t   H W N D ,   s o   i t   f i l l s   u p   t h e   e n t i r e   s p a c e .   
 
     
 
       R E C T   r e c t ; 
 
       : : G e t W i n d o w R e c t ( h W n d P a r e n t ,   & r e c t ) ;   
 
       
 
       m _ c h i l d H W n d   =   C r e a t e W i n d o w W ( s z W i n d o w C l a s s . c _ s t r ( ) ,   s z T i t l e . c _ s t r ( ) ,   W S _ C H I L D , 
 
               0 ,   0 , r e c t . r i g h t - r e c t . l e f t   ,   r e c t . b o t t o m - r e c t . t o p ,   
 
               h W n d P a r e n t ,   n u l l p t r ,   h I n s t a n c e ,   n u l l p t r ) ; 
 
 
 
       i f   ( ! m _ c h i l d H W n d ) 
 
       { 
 
 	       r e t u r n   F A L S E ; 
 
       } 
 
 
 
         / /   E n s u r e   t h a t   t h e   D i s p a t c h e r Q u e u e   i s   i n i t i a l i z e d .   T h i s   i s   r e q u i r e d   b y   t h e   C o m p o s i t o r .   
 
         a u t o   c o n t r o l l e r   =   W i n C o m p : : E n s u r e D i s p a t c h e r Q u e u e ( ) ; 
 
       
 
       S h o w W i n d o w ( h W n d P a r e n t ,   n C m d S h o w ) ; 
 
       U p d a t e W i n d o w ( h W n d P a r e n t ) ; 
 
       S h o w W i n d o w ( m _ c h i l d H W n d ,   n C m d S h o w ) ; 
 
       U p d a t e W i n d o w ( m _ c h i l d H W n d ) ; 
 
 
 
       i f   ( ! i s S e c o n d a r y ) 
 
       { 
 
               V i s u a l   v i s u a l {   n u l l p t r   } ; 
 
               C o m p o s i t o r   c o m p o s i t o r ; 
 
               D e s k t o p W i n d o w T a r g e t   t a r g e t {   n u l l p t r   } ; 
 
               a u t o   i n t e r o p   =   c o m p o s i t o r . t r y _ a s < A B I : : W i n d o w s : : U I : : C o m p o s i t i o n : : D e s k t o p : : I C o m p o s i t o r D e s k t o p I n t e r o p > ( ) ; 
 
               i n t e r o p - > C r e a t e D e s k t o p W i n d o w T a r g e t ( m _ c h i l d H W n d ,   t r u e ,   r e i n t e r p r e t _ c a s t < A B I : : W i n d o w s : : U I : : C o m p o s i t i o n : : D e s k t o p : : I D e s k t o p W i n d o w T a r g e t   * * > ( w i n r t : : p u t _ a b i ( t a r g e t ) ) ) ; 
 
               a u t o   p a r t n e r   =   c o m p o s i t o r . t r y _ a s < I C o m p o s i t o r P a r t n e r > ( ) ; 
 
               p a r t n e r - > C r e a t e S h a r e d V i s u a l ( r e i n t e r p r e t _ c a s t < A B I : : W i n d o w s : : U I : : C o m p o s i t i o n : : I V i s u a l   * * > ( w i n r t : : p u t _ a b i ( v i s u a l ) ) ) ; 
 
 
 
               H A N D L E   s h a r e d H a n d l e ; 
 
               p a r t n e r - > O p e n S h a r e d R e s o u r c e H a n d l e ( r e i n t e r p r e t _ c a s t < A B I : : W i n d o w s : : U I : : C o m p o s i t i o n : : I C o m p o s i t i o n O b j e c t   * > ( w i n r t : : g e t _ a b i ( v i s u a l . a s < C o m p o s i t i o n O b j e c t > ( ) ) ) ,   & s h a r e d H a n d l e ) ; 
 
 
 
               S T A R T U P I N F O A   c i f ; 
 
               Z e r o M e m o r y ( & c i f ,   s i z e o f ( c i f ) ) ; 
 
               c i f . c b   =   s i z e o f ( c i f ) ; 
 
 
 
               P R O C E S S _ I N F O R M A T I O N   p i ; 
 
               Z e r o M e m o r y ( & p i ,   s i z e o f ( p i ) ) ; 
 
 
 
               s t d : : s t r i n g   c m d   =   G e t C o m m a n d L i n e A ( ) ; 
 
               c m d   + =   "   S e c o n d a r y P r o c e s s " ; 
 
               C r e a t e P r o c e s s A ( N U L L ,   ( L P S T R ) c m d . c _ s t r ( ) ,   N U L L ,   N U L L ,   F A L S E ,   0 ,   N U L L ,   N U L L ,   & c i f ,   & p i ) ; 
 
 
 
               t a r g e t . R o o t ( v i s u a l ) ; 
 
               v i s u a l . R e l a t i v e S i z e A d j u s t m e n t ( {   1 ,   1   } ) ; 
 
 
 
               H A N D L E   s e c o n d a r y H a n d l e ; 
 
               D u p l i c a t e H a n d l e ( G e t C u r r e n t P r o c e s s ( ) ,   s h a r e d H a n d l e ,   p i . h P r o c e s s ,   & s e c o n d a r y H a n d l e ,   N U L L ,   F A L S E ,   D U P L I C A T E _ S A M E _ A C C E S S ) ; 
 
 
 
               C O P Y D A T A S T R U C T   C D S ; 
 
               C D S . c b D a t a   =   s i z e o f ( H A N D L E ) ; 
 
               C D S . d w D a t a   =   C D S S H A R E D H A N D L E ; 
 
               C D S . l p D a t a   =   & s e c o n d a r y H a n d l e ; 
 
 
 
               / /   W a i t   f o r   t h e   s e c o n d a r y   p r o c e s s   t o   s p a w n   i t s   w i n d o w 
 
               S l e e p ( 5 0 0 ) ; 
 
 
 
               s e c o n d a r y H w n d   =   F i n d W i n d o w W ( L " C o m p o s i t i o n T i l e s . S e c o n d a r y " ,   N U L L ) ; 
 
               S e n d M e s s a g e ( s e c o n d a r y H w n d ,   W M _ C O P Y D A T A ,   ( W P A R A M ) ( H W N D ) h W n d P a r e n t ,   ( L P A R A M ) ( L P V O I D ) & C D S ) ; 
 
 
 
               M S G   m s g ; 
 
               w h i l e   ( G e t M e s s a g e ( & m s g ,   n u l l p t r ,   0 ,   0 ) ) 
 
               { 
 
                       T r a n s l a t e M e s s a g e ( & m s g ) ; 
 
                       D i s p a t c h M e s s a g e ( & m s g ) ; 
 
               } 
 
 
 
               r e t u r n   ( i n t ) m s g . w P a r a m ; 
 
 
 
               C l o s e H a n d l e ( p i . h T h r e a d ) ; 
 
               T e r m i n a t e P r o c e s s ( p i . h P r o c e s s ,   0 ) ; 
 
 
 
               C l o s e H a n d l e ( s h a r e d H a n d l e ) ; 
 
               C l o s e H a n d l e ( s e c o n d a r y H a n d l e ) ; 
 
               
 
               r e t u r n   F A L S E ; 
 
       } 
 
       e l s e 
 
       { 
 
               m _ w i n C o m p   =   w i n r t : : m a k e _ s e l f < W i n C o m p > ( ) . d e t a c h ( ) ; 
 
               m _ w i n C o m p - > I n i t i a l i z e ( m _ c h i l d H W n d ) ; 
 
       } 
 
       
 
       r e t u r n   T R U E ; 
 
 } 
 
 
 
 / / 
 
 / /     F U N C T I O N :   W n d P r o c ( H W N D ,   U I N T ,   W P A R A M ,   L P A R A M ) 
 
 / / 
 
 / /     P U R P O S E :     P r o c e s s e s   m e s s a g e s   f o r   t h e   m a i n   w i n d o w . 
 
 / / 
 
 / /     W M _ C O M M A N D     -   p r o c e s s   t h e   a p p l i c a t i o n   m e n u 
 
 / /     W M _ P A I N T         -   P a i n t   t h e   m a i n   w i n d o w 
 
 / /     W M _ D E S T R O Y     -   p o s t   a   q u i t   m e s s a g e   a n d   r e t u r n 
 
 / / 
 
 / / 
 
 L R E S U L T   C A L L B A C K   W n d P r o c ( H W N D   h W n d ,   U I N T   m e s s a g e ,   W P A R A M   w P a r a m ,   L P A R A M   l P a r a m ) 
 
 { 
 
         s w i t c h   ( m e s s a g e ) 
 
         { 
 
         c a s e   W M _ C O M M A N D : 
 
                 { 
 
                         i n t   w m I d   =   L O W O R D ( w P a r a m ) ; 
 
                         / /   P a r s e   t h e   m e n u   s e l e c t i o n s : 
 
                         s w i t c h   ( w m I d ) 
 
                         { 
 
                         c a s e   I D M _ A B O U T : 
 
                                 D i a l o g B o x ( h I n s t ,   M A K E I N T R E S O U R C E ( I D D _ A B O U T B O X ) ,   h W n d ,   A b o u t ) ; 
 
                                 b r e a k ; 
 
                         c a s e   I D M _ E X I T : 
 
                                 D e s t r o y W i n d o w ( h W n d ) ; 
 
                                 b r e a k ; 
 
                         d e f a u l t : 
 
                                 r e t u r n   D e f W i n d o w P r o c ( h W n d ,   m e s s a g e ,   w P a r a m ,   l P a r a m ) ; 
 
                         } 
 
                 } 
 
                 b r e a k ; 
 
 	 c a s e   W M _ P O I N T E R D O W N : 
 
 	 { 
 
 	 	 / / R e d i r e c t   i n p u t   e v e n t s   t o   t h e   I n t e r a c t i o n T r a c k e r   f o r   i n p u t   e v e n t s . 
 
                 i f   ( i s S e c o n d a r y ) 
 
                 { 
 
                         P o i n t e r P o i n t   p p   =   P o i n t e r P o i n t : : G e t C u r r e n t P o i n t ( G E T _ P O I N T E R I D _ W P A R A M ( w P a r a m ) ) ; 
 
                         i f   ( m _ w i n C o m p   ! =   n u l l p t r ) 
 
                                 m _ w i n C o m p - > T r y R e d i r e c t F o r M a n i p u l a t i o n ( p p ) ; 
 
                 } 
 
                 e l s e   i f   ( s e c o n d a r y H w n d ) 
 
                 { 
 
                         P O I N T E R _ I N F O   i n f o ; 
 
                         a u t o   p o i n t e r I d   =   G E T _ P O I N T E R I D _ W P A R A M ( w P a r a m ) ; 
 
                         G e t P o i n t e r I n f o ( p o i n t e r I d ,   & i n f o ) ; 
 
 
 
                         i f   ( i n f o . p o i n t e r T y p e   = =   P T _ T O U C H ) 
 
                         { 
 
                                 C O P Y D A T A S T R U C T   C D S ; 
 
                                 C D S . c b D a t a   =   s i z e o f ( i n f o ) ; 
 
                                 C D S . d w D a t a   =   C D S P O I N T E R I N F O ; 
 
                                 C D S . l p D a t a   =   & i n f o ; 
 
 
 
                                 S e n d M e s s a g e ( s e c o n d a r y H w n d ,   W M _ C O P Y D A T A ,   ( W P A R A M ) h W n d ,   ( L P A R A M ) ( L P V O I D ) & C D S ) ; 
 
                         } 
 
                 } 
 
 	 	 b r e a k ; 
 
 	 } 
 
 
 
 
 
         c a s e   W M _ P A I N T : 
 
                 { 
 
                         P A I N T S T R U C T   p s ; 
 
                         H D C   h d c   =   B e g i n P a i n t ( h W n d ,   & p s ) ; 
 
                         E n d P a i n t ( h W n d ,   & p s ) ; 
 
                 } 
 
                 b r e a k ; 
 
 
 
 	 c a s e   W M _ S I Z E : 
 
 	 	 { 
 
 	 	 	 / / U p d a t e   t h e   c h i l d   H W N D   t o   t h e   n e w   s i z e   o f   t h e   p a r e n t   H W n d . 
 
 	 	 	 R E C T   w i n d o w R e c t ; 
 
 	 	 	 : : G e t W i n d o w R e c t ( h W n d ,   & w i n d o w R e c t ) ; 
 
 	 	 	 : : S e t W i n d o w P o s ( m _ c h i l d H W n d ,   H W N D _ T O P , 0 , 0 ,   w i n d o w R e c t . r i g h t   -   w i n d o w R e c t . l e f t ,   w i n d o w R e c t . b o t t o m   -   w i n d o w R e c t . t o p ,   S W P _ N O Z O R D E R ) ; 
 
 	 	 	 i f ( m _ w i n C o m p   ! = n u l l p t r ) 
 
 	 	 	 	 m _ w i n C o m p - > U p d a t e V i e w P o r t ( t r u e ) ; 
 
 	 	 } 
 
 	 	 b r e a k ; 
 
         c a s e   W M _ D E S T R O Y : 
 
                 P o s t Q u i t M e s s a g e ( 0 ) ; 
 
                 b r e a k ; 
 
 
 
         c a s e   W M _ C O P Y D A T A : 
 
         { 
 
                 a u t o   C D S   =   ( P C O P Y D A T A S T R U C T ) l P a r a m ; 
 
                 i f   ( i s S e c o n d a r y ) 
 
                 { 
 
                         i f   ( C D S - > d w D a t a   = =   C D S S H A R E D H A N D L E ) 
 
                         { 
 
                                 r e c e i v e d H a n d l e   =   * ( H A N D L E * ) C D S - > l p D a t a ; 
 
                                 h a n d l e R e c e i v e d   =   t r u e ; 
 
 
 
                                 D W O R D   p i d ; 
 
                                 G e t W i n d o w T h r e a d P r o c e s s I d ( ( H W N D ) w P a r a m ,   & p i d ) ; 
 
                                 p a r e n t P r o c c e s s   =   O p e n P r o c e s s ( P R O C E S S _ T E R M I N A T E ,   F A L S E ,   p i d ) ; 
 
                         } 
 
                         e l s e   i f   ( C D S - > d w D a t a   = =   C D S P O I N T E R I N F O   & &   m _ w i n C o m p ) 
 
                         { 
 
                                 P O I N T E R _ I N F O   p o i n t e r I n f o   =   * ( P O I N T E R _ I N F O * ) C D S - > l p D a t a ; 
 
                                 m _ w i n C o m p - > T r y R e d i r e c t F o r M a n i p u l a t i o n ( p o i n t e r I n f o ) ; 
 
                         } 
 
                 } 
 
                 b r e a k ; 
 
         } 
 
         d e f a u l t : 
 
                 r e t u r n   D e f W i n d o w P r o c ( h W n d ,   m e s s a g e ,   w P a r a m ,   l P a r a m ) ; 
 
         } 
 
         r e t u r n   0 ; 
 
 } 
 
 
 
 / /   M e s s a g e   h a n d l e r   f o r   a b o u t   b o x . 
 
 I N T _ P T R   C A L L B A C K   A b o u t ( H W N D   h D l g ,   U I N T   m e s s a g e ,   W P A R A M   w P a r a m ,   L P A R A M   l P a r a m ) 
 
 { 
 
         U N R E F E R E N C E D _ P A R A M E T E R ( l P a r a m ) ; 
 
         s w i t c h   ( m e s s a g e ) 
 
         { 
 
         c a s e   W M _ I N I T D I A L O G : 
 
                 r e t u r n   ( I N T _ P T R ) T R U E ; 
 
 
 
         c a s e   W M _ C O M M A N D : 
 
                 i f   ( L O W O R D ( w P a r a m )   = =   I D O K   | |   L O W O R D ( w P a r a m )   = =   I D C A N C E L ) 
 
                 { 
 
                         E n d D i a l o g ( h D l g ,   L O W O R D ( w P a r a m ) ) ; 
 
                         r e t u r n   ( I N T _ P T R ) T R U E ; 
 
                 } 
 
                 b r e a k ; 
 
         } 
 
         r e t u r n   ( I N T _ P T R ) F A L S E ; 
 
 } 
 
 