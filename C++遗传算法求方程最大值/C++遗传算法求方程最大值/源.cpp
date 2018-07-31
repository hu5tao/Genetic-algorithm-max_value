    #include <iostream>  
    #include <armadillo>  
      
    int ma()  
    {  
        arma::mat A = arma::randu<arma::mat>(4, 5) * 10;  
        arma::mat B = arma::randu<arma::mat>(4, 5) * 10;  
        arma::mat C = A % B;  
        A.print("A = \n");  
        B.print("B = \n");  
        C.print("A .* B = \n");  
        return 0;  
    }  