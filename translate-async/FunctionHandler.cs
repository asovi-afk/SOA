using Microsoft.AspNetCore.Http;
using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;
using System.IO;
using Newtonsoft.Json;

namespace Function
{
    public class FunctionHandler
    {
        public async Task<(int, string)> Handle(HttpRequest req)
        {
            int size = 100;
            byte[] buffer = new byte[size];
            int len = await req.Body.ReadAsync(buffer, 0, size);
            
            string message = System.Text.Encoding.Default.GetString(buffer, 0, len);
    

            var client = new HttpClient();
            var request = new HttpRequestMessage {
                Method = HttpMethod.Post,
                RequestUri = new Uri("https://google-translate1.p.rapidapi.com/language/translate/v2"),
                Headers = 
                {
                    { "X-RapidAPI-Host", "google-translate1.p.rapidapi.com"},
                    { "X-RapidAPI-Key", "6bbcdca72fmshf0879d5043f8eb7p152774jsn2d6a791a1bc9"}
                },
                Content = new FormUrlEncodedContent(new Dictionary<string, string> {
                    {"q", message},
                    {"target", "fr"},
                    {"source", "en"}
                })
            };
            using (var response = await client.SendAsync(request))
            {
                try {
                    response.EnsureSuccessStatusCode();
                    var jsonResponse = await response.Content.ReadAsStringAsync();
                    Root data = new Root();
                    JsonConvert.PopulateObject(jsonResponse, data);
                    
                    return (200, data.data.translations[0].translatedText);
                } catch ( Exception ex) {
                    return (202, response.ReasonPhrase);
                }
            }
        }
    }

    public class Data
    {
        public List<Translation> translations { get; set; }
    }

    public class Root
    {
        public Data data { get; set; }
    }

    public class Translation
    {
        public string translatedText { get; set; }
    }

}