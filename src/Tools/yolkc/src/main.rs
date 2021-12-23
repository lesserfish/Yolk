mod lexer;

fn main()
{
    let int_keyword_rule = lexer::Derivation::new(&"keyword".to_string(), &"type".to_string(),&"^int(\\W)$".to_string());
    let space_rule = lexer::Derivation::new(&"space".to_string(), &"space".to_string() ,&"^( )".to_string());
    let identifier_rule  = lexer::Derivation::new(&"identifier".to_string(), &"identifier".to_string(), &"^([a-z]|[A-Z]|_)(\\w)*(\\W)$".to_string());
    let colon_rule = lexer::Derivation::new(&"symbol".to_string(), &"symbol".to_string(), &"^;".to_string());
    let equal_rule = lexer::Derivation::new(&"symbol".to_string(),&"symbol".to_string(), &"^=$".to_string());
    let integer_rule  = lexer::Derivation::new(&"integer".to_string(), &"value".to_string(), &"([0-9])+([^\\.\\w])".to_string());
    let double_rule  = lexer::Derivation::new(&"double".to_string(), &"value".to_string(), &"^([0-9])+\\.([0-9])+([^f\\w])$".to_string());
    let float_rule  = lexer::Derivation::new(&"float".to_string(), &"value".to_string(), &"^([0-9])+\\.([0-9])+f(\\D)$".to_string());
    
    let mut lx = lexer::Lexer::new();
    
    lx.add_derivation(int_keyword_rule, 0, -1);
    lx.add_derivation(space_rule, 2, 0);
    lx.add_derivation(identifier_rule, 1, -1);
    lx.add_derivation(colon_rule, 2, 0);
    lx.add_derivation(equal_rule, 2, 0);
    lx.add_derivation(integer_rule, 5, -1);
    lx.add_derivation(double_rule, 1, -1);
    lx.add_derivation(float_rule, 1, -1);
    lx.set_input(&"int x = 3.14f;int y = 3.12=121;".to_string());

    while !lx.done()
    {
        let output = lx.get_next_token();
        let status = output.0;
        if !status
        {
      //      println!("Error message: {}", output.1);
            break;
        }
 //       let token = output.2;
 //       println!("Token: ({0}:{1})", token.token_name.to_string(), token.token_value.to_string());
    }

}