use proc_macro::TokenStream;
use quote::quote;
use syn::{Token, Type, parse_macro_input, punctuated::Punctuated};

#[proc_macro]
pub fn typelist(input: TokenStream) -> TokenStream {
    let types = parse_macro_input!(input with Punctuated::<Type, Token![,]>::parse_terminated);

    let expanded = build_typelist(types.iter().collect());

    TokenStream::from(expanded)
}

fn build_typelist(types: Vec<&syn::Type>) -> proc_macro2::TokenStream {
    if types.is_empty() {
        quote! { NullType }
    } else {
        let head = types[0];
        let tail = build_typelist(types[1..].to_vec());
        quote! { Typelist<#head, #tail> }
    }
}
