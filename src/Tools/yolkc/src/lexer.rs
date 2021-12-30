#![allow(dead_code)]
use regex::Regex;

#[derive(Clone)]
#[repr(C)]
pub struct Token
{
    pub token_name : String,
    pub token_class : String,
    pub token_value : String
}
impl Token
{
    pub fn new(name : &String, class : &String, value : &String) -> Token
    {
        let token = Token { token_name : name.to_string(), 
                            token_class : class.to_string(), 
                            token_value : value.to_string()};
        return token;
    }
    pub fn generic() -> Token
    {
        let token = Token::new( &"".to_string(), 
                                &"".to_string(), 
                                &"".to_string());
        return token;
    }
}

#[derive(Clone)]
pub struct Derivation
{
    token_name : String,
    token_class : String,
    derivation_regex : Regex,
}
impl Derivation
{
    pub fn new(name : &String, class : &String, regex : &String) -> Derivation
    {
        let derivation = Derivation {   token_name : name.to_string(),
                                        token_class : class.to_string(),
                                        derivation_regex : Regex::new(&regex.to_string()).unwrap()};
        return derivation;
    }
    pub fn accepts(&self, input : &String) -> (bool, Token)
    {
        let input_length = input.chars().count();

        if input_length < 1 {
            return (false, Token::generic());
        }

        let match_result = self.derivation_regex.is_match(input);

        if !match_result {
            return (false, Token::generic());
        }

        let token = self.get_token(input);
        return (true, token);
    }

    fn get_token(&self, input : &String) -> Token
    {
        let input_length = input.chars().count();
        let end_index = if input_length > 1 {input_length - 1} else {input_length};

        let value = &input[0..end_index].to_string();
        let token = Token::new(&self.token_name, &self.token_class, &value);
        
        return token;
    }
}

pub struct Lexer
{
    derivation_book : Vec<(Derivation, u32, isize)>,
    input : String
}

impl Lexer
{
    pub fn new() -> Lexer
    {
        let lexer = Lexer {derivation_book : Vec::new(), input : "".to_string()};
        return lexer;
    }
    pub fn set_input(&mut self, input : &String)
    {
        self.input = input.to_string();
    }
    pub fn add_derivation(&mut self, derivation : Derivation, priority : u32, script_shift : isize)
    {
        self.derivation_book.push((derivation, priority, script_shift));
    }
    pub fn clear(&mut self)
    {
        self.derivation_book.clear();
    }
    pub fn get_next_token(&mut self) -> (bool , String , Token)
    {
        let mut accepted_tokens : Vec<(Token, u32, isize)> = Vec::new();
        let mut accepted_status = false;

        let input_length = self.input.chars().count();
        let mut index = 0;
        while index <= input_length
        {
            let input_segment = &self.input[0..index];

            for derivation in &self.derivation_book
            {
                let pair = derivation.0.accepts(&input_segment.to_string());
                if pair.0
                {
                    accepted_tokens.push((pair.1, derivation.1, derivation.2));
                    accepted_status = true;
                }
            }
            if accepted_status
            {
                break;
            }

            index += 1;
        }

        if !accepted_status
        {
            let log = "Error! Could not match the remainder of string. Remainder: ".to_string() + &self.input;
            return (false, log, Token::generic());
        }

        let mut best_priority = accepted_tokens[0].1;
        let mut best_token = Token::generic();
        let mut shift = 0;
        for pair in accepted_tokens
        {
            if pair.1 <= best_priority
            {
                best_token = pair.0;
                best_priority = pair.1;
                shift = pair.2;
            } 
        } 
        
        let mut index_cast = index as isize;
        index_cast += shift;
        index_cast = if index_cast < 0 {0} else {index_cast};
        index = index_cast as usize;

        self.input = self.input[index..].to_string();

        return (true, "ok!".to_string(), best_token);
    }

    pub fn done(&self) -> bool
    {
        if self.input.chars().count() > 0
        {
            return false;
        }
        return true;
    }
}